// Circular Queue
// 2025-02-05
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE		5

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

void queue_print(QueueType* q)
{
	printf("QUEUE(front = %d rear = %d) = ", q->front, q->rear);
	if (!is_empty(q))
	{
		int i = q->front;
		do 
		{
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
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

element peek(QueueType* q)
{
	if (is_empty(q))
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main()
{
	element item = 0;
	QueueType q;

	init_queue(&q);

	printf("--enqueue--\n");
	while (!is_full(&q))
	{
		printf("input >> ");
		scanf("%d", &item);
		enqueue(&q, item);
		queue_print(&q);
	}
	printf("Quere is full.\n\n");

	printf("--dequeue--\n");
	while (!is_empty(&q))
	{
		item = dequeue(&q);
		printf("dequeue = %d\n", item);
		queue_print(&q);
	}
	printf("Queue is empty\n");

	return 0;
}