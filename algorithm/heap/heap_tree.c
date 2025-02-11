// 2025-02-11
// 최대 힙 구현

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT		200

typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} heapType;

// 동적 할당 생성 함수
heapType* create()
{
	return (heapType*)malloc(sizeof(heapType));
}

void init(heapType* h)
{
	h->heap_size = 0;
}

void insert_max_heap(heapType* h, element item)
{
	int i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(heapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; // 삭제하려는 값 저장
	temp = h->heap[(h->heap_size)--]; // 마지막 노드 저장 후 크기 감소
	parent = 1;
	child = 2; // 왼쪽 자식 부터

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key) // 오른쪽 자식이 더 크면
		{
			child++; // 오른쪽 자식으로
		}

		if (temp.key >= h->heap[child].key)	break; // 자리를 찾으면 반복 종료

		h->heap[parent] = h->heap[child]; // 자식을 부모로 올림
		parent = child; 
		child *= 2; // 한단계 아래로
	}
	h->heap[parent] = temp; // 최종 위치에 삽입
	return item; // 삭제한 값 반환 
}


int main()
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;
	heapType* heap;

	heap = create();
	init(heap);

	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);

	e4 = delete_max_heap(heap);		printf("< %d > ", e4.key);
	e5 = delete_max_heap(heap);		printf("< %d > ", e5.key);
	e6 = delete_max_heap(heap);		printf("< %d > ", e6.key);

	free(heap);
	return 0;
}