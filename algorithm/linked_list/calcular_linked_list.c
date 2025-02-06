// Linked List
// 2025-02-05
// 원형 연결 리스트에서 Head는 마지막 노드임 - 중요 개념
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode{
	element data;
	struct ListNode* link;
}ListNode;

//선단에 삽입
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	if (head == NULL)
	{
		head = p;
		p->link = head;
	}
	else
	{
		p->link = head->link;
		head->link = p;
	}
	return head;
}

//후단에 삽입
ListNode* insert_last(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	if (head == NULL)
	{
		head = p;
		p->link = head;
	}
	else
	{
		p->link = head->link;
		head->link = p;
		head = p;
	}
	return head;
}

// 선단 삭제
ListNode* delete_first(ListNode* head)
{
	if (head == NULL) return;

	ListNode* removed = head->link;

	if (head == removed) { // 리스트에 노드가 하나만 있을 경우
		free(head);
		return NULL;
	}

	head->link = removed->link;
	free(removed);

	return head;
}

// 리스트 전체 삭제
void delete_list(ListNode* head)
{
	ListNode* p = head->link; // list의 첫번째 노드로 설정
	ListNode* removed; // 삭제할 노드를 담을 공간


	while (p != head)
	{
		removed = p;
		p = p->link;
		free(removed);
	}
	free(head);
}

//특정 값 탐색
ListNode* search_list(ListNode* head, element find)
{
	if (head == NULL) return NULL;
	
	if (head->data == find) return head;  // head가 찾는 값이면 바로 반환

	ListNode* p = head->link;

	while (p != head)
	{
		if (p->data == find)
		{
			return p;
		}
		p = p->link;
	}

	return NULL;
}

// 출력
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;

	p = head->link;
	do {
		printf("%d -> ", p->data);
		p = p->link;
	} while (p != head);

	printf("%d -> ", p->data);
}


int main()
{
	ListNode* head = NULL;

	head = insert_last(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 40);
	head = insert_first(head, 10);

	print_list(head);


	delete_list(head);
	return 0;
}