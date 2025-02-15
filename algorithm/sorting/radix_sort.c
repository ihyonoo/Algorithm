// 2025-02-15
// Radix Sort: 기수 정렬 프로그램

#include <stdio.h>
#include <stdlib.h>

#define BUCKETS			10		//버켓수
#define DIGITS			3		//최대 자리수
#define MAX_QUEUE_SIZE	100		//최대 큐 사이즈

// circular queue 코드 추가
typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		printf("queue overflow\n");
		return;
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q)) {
		printf("queue underflow");
		exit(1);
	}

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void radix_sort(int list[], int n)
{
	QueueType queues[BUCKETS]; //버켓의 수만큼 큐 배열 생성

	int factor = 1; //반복할 때마다 자리수를 올려주는 변수 1, 10 ,100 ,1000 .......


	//각 버켓(큐)초기화
	for (int i = 0; i < BUCKETS; i++) {
		init(&queues[i]);
	}

	printf("<정렬 과정>\n");

	for (int d = 0; d < DIGITS; d++)
	{
		printf("Disit : %d\n", d + 1);

		//1의 자리 숫자를 읽어서 순차적으로 enqueue
		for (int i = 0; i < n; i++) {
			enqueue(&queues[(list[i] / factor) % 10], list[i]); //해당 숫자에 맞는 버킷 요소 삽입
		}

		//queue[]에 저장된 숫자를 0번부터 시작해서 순차적으로 dequeu()해서 list[]에 새로 저장
		for (int b = 0, i = 0; b < BUCKETS; b++)
		{
			printf("Bucket[%d] : ", b);

			if (is_empty(&queues[b]))
				printf("Empty");

			while (!is_empty(&queues[b])) {
				list[i] = dequeue(&queues[b]);	//버킷에서 요소를 제거 후 리스트에 재삽입
				printf(" %d ", list[i++]);
			}
			printf("\n");
		}
		factor *= 10; //다른 자릿수로 이동
	}
}

int main() {
	FILE* fp;
	int list[MAX_QUEUE_SIZE] = { 0 };
	int n = 0;

	fp = fopen("data1.txt", "r");

	if (fp == NULL) {
		printf("file not found");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &list[n]);
		n++;
	}

	printf("<정렬 전 데이터>\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d > ", list[i]);
	}

	radix_sort(list, n);

	printf("<정렬 후 데이터>\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d > ", list[i]);
	}

	fclose(fp);
	return 0;
}