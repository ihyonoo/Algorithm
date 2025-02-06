//Linked List
//2025-02-05
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {
	element data;
	struct ListNode* link;
}ListNode;

//선단에 삽입
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

//pre 뒤에 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

//head 삭제
ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	
	if (head == NULL) return NULL;
	
	removed = head;
	head = removed->link;
	free(removed);

	return head;
}

//pre 뒤 노드 삭제
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	
	removed = pre->link;
	pre->link = removed->link;
	free(removed);

	return head;
}

// 리스트 전체 삭제
void delete_list(ListNode* head)
{
	ListNode* removed;

	while (head != NULL)
	{
		removed = head;
		head = head->link;
		free(removed);
	}
}

//값 탐색
ListNode* search_list(ListNode* head, element find)
{
	ListNode* p = head;

	while (p != NULL)
	{
		if (p->data == find) 
			return p;

		p = p->link;
	}

	return NULL; //탐색 실패
}

//출력
void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
	{
		printf("%d -> ", p->data);
	}
	printf("NULL\n");
}

int main()
{
	ListNode* head = NULL;

	for (int i = 0; i < 5; i++)
	{
		head = insert_first(head, i);
		print_list(head);
	}

	for (int i = 0; i < 5; i++)
	{
		head = delete_first(head);
		print_list(head);
	}

	delete_list(head);
	return 0;
}