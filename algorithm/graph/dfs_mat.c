// 2025-02-12
// DFS: depth first search
// 인접 행렬을 이용한 깊이 우선 탐색

#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_VERTICES		50


int visited[MAX_VERTICES];

typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;



// init
void init(GraphType* g)
{
	g->n = 0;

	for (int row = 0; row < MAX_VERTICES; row++)
		for (int cul = 0; cul < MAX_VERTICES; cul++)
			g->adj_mat[row][cul] = 0;
}

// insert vertex
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "vertex Overflow\n");
		return;
	}
	g->n++;
}

// insert edge
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "error\n");
		return;
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// 깊이 우선 탐색
void dfs_mat(GraphType* g, int v)
{
	visited[v] = TRUE;	// v 방문 표시 
	printf("정점 %d -> ", v);

	for (int w = 0; w < g->n; w++)
	{
		if (g->adj_mat[v][w] && !visited[w])	// 연결 되어 있고 방문하지 않았으면
		{
			dfs_mat(g, w);
		}
	}
}


int main()
{
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i < 4; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);

	printf("DFS\n");
	dfs_mat(g, 0);

	free(g);
	return 0;
}