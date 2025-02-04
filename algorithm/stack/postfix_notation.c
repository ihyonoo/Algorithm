#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE		100

typedef char element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s))
	{
		printf("Stack overflow\n");
		return; // 심각한 오류는 아니기 때문에 exit가 아닌 return
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s))
	{
		printf("Stack underflow\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(s))
	{
		printf("Stack underflow\n");
		exit(1);
	}
	return s->data[s->top];
}

int eval(char exp[])
{
	int op1, op2, value = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);

	for (int i = 0; i < len; i++)
	{
		ch = exp[i];

		if (ch != '+' && ch != '-' && ch != '/' && ch != '*')
		{
			value = ch - '0';
			push(&s, value);
		}
		else
		{
			op2 = pop(&s);
			op1 = pop(&s);

			switch (ch)
			{
			case '+':
				push(&s, op1 + op2);
				break;
			case '-':
				push(&s, op1 - op2);
				break;
			case '/':
				push(&s, op1 / op2);
				break;
			case '*':
				push(&s, op1 * op2);
				break;
			}

		}
	}
	return pop(&s);
}

int main()
{
	printf("result = %d\n", eval("82/3-32*+"));

	return 0;
}