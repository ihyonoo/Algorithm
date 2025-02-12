// 2025-02-12
// 인접 리스트 구현

#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_VERTICES		50


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

// print
void print_adj_list(GraphType* g)
{
	for (int i = 0; i < g->n; i++)
	{
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (p != NULL)
		{
			printf("-> %d ", p->vertex);
			p = p->link;
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
	insert_edge(g, 1, 0);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 0);
	insert_edge(g, 0, 3);
	insert_edge(g, 3, 0);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 3, 2);

	print_adj_list(g);

	free(g);
	return 0;
}