// 2025-02-06
// Linked Calcular Queue

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

// Queue ADT
typedef struct { 
	QueueNode* front;
	QueueNode* rear;
}LinkedQueueType;

// init
void init(LinkedQueueType* q)
{
	q->front = q->rear = NULL;
}

// empty
int is_empty(LinkedQueueType* q)
{
	return (q->front == NULL); 
}

// enqueue
void enqueue(LinkedQueueType* q, element value)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));

	temp->data = value;

	if (is_empty(q))
	{
		q->front = temp;
		q->rear = temp;
		temp->link = temp;
	}
	else
	{
		q->rear->link = temp;
		temp->link = q->front;
		q->rear = temp;
	}
}

//dequeue
element dequeue(LinkedQueueType* q)
{
	if (is_empty(q))
	{
		fprintf(stderr, "Queue Underflow\n");
		exit(1);
	}

	QueueNode* temp = q->front;
	element value = temp->data;

	if (q->front == q->rear) // 큐가 1개 라면
	{
		q->front = q->rear = NULL;
	}
	else
	{
		q->front = q->front->link;
		q->rear->link = q->front;
	}
	
	free(temp);
	return value;
}

// 출력
void print_queue(LinkedQueueType* q) 
{
	QueueNode* p = q->front;

	if (!is_empty(q))
	{
		do {
			printf("%d -> ", p->data);
			p = p->link;
		} while (p != q->front);
	}
	printf("\n");
}


int main()
{
	LinkedQueueType q;

	init(&q);

	enqueue(&q, 1);	print_queue(&q);
	enqueue(&q, 2);	print_queue(&q);
	enqueue(&q, 3);	print_queue(&q);

	dequeue(&q);	print_queue(&q);
	dequeue(&q);	print_queue(&q);
	dequeue(&q);	print_queue(&q);

	return 0;
}