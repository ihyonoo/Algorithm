// 2025-02-13
// Topology Sort: 그래프 위상 정렬 프로그램

#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_VERTICES		50
#define MAX_STACK_SIZE		100

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;		// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// init
void init_graph(GraphType* g)
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

//////////////////////스택 코드/////////////////
typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;


void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s))
	{
		printf("Stack overflow\n");
		return; // 심각한 오류는 아니기 때문에 exit가 아닌 return
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s))
	{
		printf("Stack underflow\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

//////////////////////////////////////////////////////////////////////

// Topology Sort
int topo_sort(GraphType* g)
{
	int i, w, u;
	StackType s;
	GraphNode* node;

	int* in_degree = (int*)malloc(g->n * sizeof(int));

	// init
	for (i = 0; i < g->n; i++)
		in_degree[i] = 0;

	
	// 진입 차수 계산
	for (i = 0; i < g->n; i++)
	{
		GraphNode* node = g->adj_list[i];

		while (node != NULL)
		{
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	// 진입 차수가 0인 정점을 스택에 push
	init_stack(&s);
	for (i = 0; i < g->n; i++)
	{
		if (in_degree[i] == 0)
			push(&s, i);
	}

	// 위상 정렬 수행
	while (!is_empty(&s))
	{
		w = pop(&s);
		printf("%d -> ", w);

		node = g->adj_list[w];		//w와 연결된 모든 간선 탐색
		while (node != NULL)		
		{
			u = node->vertex;		// w에 연결된 정점
			in_degree[u]--;			// 진입 차수 차감

			if (in_degree[u] == 0)	// 진입 차수가 0 이면
				push(&s, u);		// push

			node = node->link;
		}
	}

	free(in_degree);
	return (i == g->n);				// 정렬이 성공하면 1, 실패하면 0
}

int main()
{
	GraphType g;

	init_graph(&g);

	insert_vertex(&g, 0);
	insert_vertex(&g, 1);
	insert_vertex(&g, 2);
	insert_vertex(&g, 3);
	insert_vertex(&g, 4);
	insert_vertex(&g, 5);

	insert_edge(&g, 0, 2);
	insert_edge(&g, 0, 3);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 3, 5);
	insert_edge(&g, 4, 5);
	
	topo_sort(&g);
	
	// 그래프 메모리 해제 생략
	return 0;
}
