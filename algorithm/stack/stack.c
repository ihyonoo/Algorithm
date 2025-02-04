#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE		100

typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType *s)
{
	return (s->top == -1);
}

int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE -1));
}

void push(StackType *s, element item)
{
	if (is_full(s))
	{	
		printf("Stack overflow\n");
		return; // 심각한 오류는 아니기 때문에 exit가 아닌 return
	}
	s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
	if (is_empty(s))
	{
		printf("Stack underflow\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

element peek(StackType *s)
{
	if (is_empty(s))
	{
		printf("Stack underflow\n");
		exit(1);
	}
	return s->data[s->top];
}

int main()
{
	StackType s;

	init_stack(&s);

	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));

	return 0;
}