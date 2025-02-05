// Double-ended Queue
// 2025-02-05
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE		5

typedef int element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} DequeType;


// 초기화
void init_queue(DequeType* q)
{
	q->rear = 0;
	q->front = 0;
}

int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // front가 rear보다 앞에 있으면 full
}

int is_empty(DequeType* q)
{
	return (q->front == q->rear); // front와 rear가 같으면 empty
}

void deque_print(DequeType* q)
{
	printf("DEQUE(front = %d rear = %d) = ", q->front, q->rear);
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

void add_rear(DequeType* q, element item)
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
element delete_front(DequeType* q)
{
	if (is_empty(q))
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void add_front(DequeType* q, element item)
{
	if (is_full(q))
	{
		printf("Queue Overflow\n");
		return;
	}
	q->data[q->front] = item;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_front(DequeType* q)
{
	if (is_empty(q))
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	return q->data[q->rear];
}

int main()
{
	DequeType q;

	init_queue(&q);

	for (int i = 0; i < 3; i++)
	{
		add_front(&q, i);
		deque_print(&q);
	}

	for (int i = 0; i < 3; i++)
	{
		delete_rear(&q);
		deque_print(&q);
	}

	return 0;
}