// 2025-02-11
// 인접 행렬(adjacency matrix) 구현
// 무방향 그래프

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES		50

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

// print
void print_adj_mat(GraphType* g)
{
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
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
	
	print_adj_mat(g);
	
	free(g);
	return 0;
}