// 2025-02-12
// Kruskal의 MST 알고리즘 프로그램

#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_VERTICES		100
#define INF					1000L


int parent[MAX_VERTICES];

struct Edge {
	int start;
	int end;
	int weight;
};

typedef struct GraphType {
	int n;			// 간선의 개수
	int nvertex;	// 정점의 개수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;


//
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;	
}

// curr가 속한 집합을 find
int set_find(int curr)
{
	if (parent[curr] == -1)		// -1이면 자기 자신이 부모
		return curr;
	
	while (parent[curr] != -1)
		curr = parent[curr];

	return curr;
}

// 두 개의 집합을 합침
void set_union(int a, int b)
{
	int root1 = set_find(a);
	int root2 = set_find(b);

	if (root1 != root2)
		parent[root1] = root2;
}

// init GraphType
void graph_init(GraphType* g)
{
	g->n = g->nvertex = 0;

	for (int i = 0; i < 2 * MAX_VERTICES; i++)
	{
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// insert edge
void insert_edge(GraphType* g, int s, int e, int w)
{
	g->edges[g->n].start = s;
	g->edges[g->n].end = e;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort를 사용하기 위하여 정의한 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	
	return (x->weight - y->weight);
}

void kruskal(GraphType* g)
{
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->nvertex);	// 정점의 개수 만큼 배열 초기화

	qsort(g->edges, g->n, sizeof(struct Edge), compare);
	
	printf("Kruskal MST Algorithm \n");
	int i = 0;
	while (edge_accepted < (g->nvertex - 1)) // 신장트리: 간선의 개수 = 정점의 개수 -1개
	{
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);

		if (uset != vset)
		{
			printf("Edge (%d, %d) %d 선택\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}


int main()
{
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	g->nvertex = 7;

	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);

	kruskal(g);

	free(g);
	return 0;
}