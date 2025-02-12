// 2025-02-12
// BFS: breath first search
// 인접 리스트를 이용한 너비 우선 탐색

#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_VERTICES		50
#define MAX_QUEUE_SIZE		10

//////////////////////////////QUEUE 코드/////////////////////////////////////////////////
typedef int element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;


//queue 초기화
void init_queue(QueueType* q)
{
	q->rear = 0;
	q->front = 0;
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // front가 rear보다 앞에 있으면 full
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear); // front와 rear가 같으면 empty
}

// 삽입
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
	{
		printf("Queue Overflow\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

//삭제
element dequeue(QueueType* q)
{
	if (is_empty(q))
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
/////////////////////////////////////////////////////////////////////////////////////////



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

void bfs_list(GraphType* g, int v)
{
	GraphNode* w;
	QueueType q;
	
	init_queue(&q);

	visited[v] = TRUE;
	printf("%d -> ", v);
	
	enqueue(&q, v);
	while (!is_empty(&q))
	{
		v = dequeue(&q);

		for (w = g->adj_list[v]; w; w = w->link)
		{
			if (!visited[w->vertex])
			{
				visited[w->vertex] = TRUE;
				printf("%d -> ", w->vertex);
				enqueue(&q, w->vertex);
			}
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

	bfs_list(g, 0);

	free(g);
	return 0;
}