// 2025-02-11
// Heap Sort

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT		200

typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 동적 할당 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType* h)
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

// sort
void heap_sort(element a[], int n)
{
	HeapType* h;

	h = create();
	init(h);

	for (int i = 0; i < n; i++)
	{
		insert_max_heap(h, a[i]);
	}

	for (int i = (n - 1); i >= 0; i--)
	{
		a[i] = delete_max_heap(h);
	}
	
	free(h);
}

int main()
{
	element list[8] = { 23, 56, 11, 9, 56, 99, 27, 34 };
	
	heap_sort(list, 8);

	for (int i = 0; i < 8; i++)
	{
		printf("%d ", list[i].key);
	}
	printf("\n");

	return 0;
}

