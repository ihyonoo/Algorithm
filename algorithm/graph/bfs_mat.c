// 2025-02-12
// BFS: breath first search
// 인접 행렬을 이용한 너비 우선 탐색

#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_QUEUE_SIZE		10
#define MAX_VERTICES		50

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

void bfs_mat(GraphType* g, int v)
{
	QueueType q;
	init_queue(&q);

	visited[v] = TRUE;
	printf("%d -> ", v);

	enqueue(&q, v);
	while (!is_empty(&q))
	{
		v = dequeue(&q);							// dequeue

		for (int w = 0; w < g->n; w++)				// 모든 인접 정점을 enqueue
		{
			if (g->adj_mat[v][w] && !visited[w])	// 연결되어 있고 방문하지 않았으면
			{
				visited[w] = TRUE;
				printf("%d -> ", w);
				enqueue(&q, w);
			}
		}
	}
}


int main()
{
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i < 6; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 1, 5);


	printf("BFS\n");
	bfs_mat(g, 0);

	free(g);
	return 0;
}