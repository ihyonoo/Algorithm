// 2025-02-12
// DFS: depth first search
// 인접 리스트를 이용한 깊이 우선 탐색


#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_VERTICES		50

int visited[MAX_VERTICES];

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;


// init
void init(GraphType* g)
{
	g->n = 0;

	for (int v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// insert vertex
void insert_vertex(GraphType* g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES)
	{
		fprintf(stderr, "Vertex Overflow\n");
		return;
	}

	g->n++;
}

// insert edge
void insert_edge(GraphType* g, int u, int v)
{
	if (u >= g->n || v >= g->n)
	{
		fprintf(stderr, "error\n");
		return;
	}

	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));

	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

// DFS (깊이 우선 탐색)
void dfs_list(GraphType* g, int v)
{
	GraphNode* w;

	visited[v] = TRUE;
	printf("%d -> ", v);

	for (w = g->adj_list[v]; w; w = w->link)
	{
		if (!visited[w->vertex])
		{
			dfs_list(g, w->vertex);
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
	insert_edge(g, 1, 0);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 0);
	insert_edge(g, 0, 3);
	insert_edge(g, 3, 0);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 3, 2);

	dfs_list(g, 0);

	free(g);
	return 0;
}