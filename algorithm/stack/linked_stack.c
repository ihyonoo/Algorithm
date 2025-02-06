// 2025-02-06
// Stack - Linked List

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

// 초기화
void init(LinkedStackType* s)
{
	s->top = NULL;
}

//empty
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

// push
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// pop
element pop(LinkedStackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "Stack Underflow\n");
		exit(1);
	}
	
	StackNode* temp = s->top;
	int data = temp->data;
	s->top = s->top->link;
	
	free(temp);
	return data;
}

element peek(LinkedStackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "Stack Underflow\n");
		exit(1);
	}

	return s->top->data;
}

// 출력
void print_stack(LinkedStackType* s)
{
	for (StackNode* p = s->top; p != NULL; p = p->link)
	{
		printf("%d -> ", p->data);
	}
	printf("NULL\n");
}


int main()
{
	LinkedStackType s;
	
	init(&s);

	push(&s, 1); print_stack(&s);
	push(&s, 2); print_stack(&s);
	push(&s, 3); print_stack(&s);

	pop(&s); print_stack(&s);
	pop(&s); print_stack(&s);
	pop(&s); print_stack(&s);
	


	return 0;
}