// 2025-02-06
// Double Linked List
// head는 리스트의 첫 번째 노드를 가리키는 포인터가 아니며 데이터를 갖고 있지 않는다
// 다만 삽입 삭제 알고리즘을 간편하게 하기 위하여 존재

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

//before 오른쪽에 삽입
void dinsert(DListNode* before, element value)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = value;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 노트 removed 삭제
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

// 이중 연결 리스트 출력
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		printf("<- %d -> ", p->data);
	}
	printf("\n");
}

int main()
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));

	init(head);

	printf(" --insert--\n");
	for (int i = 0; i < 5; i++)
	{
		dinsert(head, i);
		print_dlist(head);
	}

	printf("\n --delete--\n");
	for (int i = 0; i < 5; i++)
	{
		print_dlist(head);
		ddelete(head, head->rlink);
	}

	free(head);
	return 0;
}