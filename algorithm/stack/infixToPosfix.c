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

// 연산자의 우선순위 반환
int prec(char op)
{
	switch (op)
	{
	case '(': case ')': 
		return 0;
	case '+': case '-':
		return 1;
	case '*': case '/':
		return 2;
	}

	return -1;
}



// 피연산자는 바로 출력
// 연산자는 우선순위를 비교해서 pop& push
// 여는 괄호는 push, 닫는 괄호를 만나면 여는 괄호까지 pop
// 끝나고 스택에 남은 연산자는 다 pop해서 출력


// infix to posfix
void infix_to_posfix(char exp[])
{
	char ch, top_op;
	int len = strlen(exp);
	StackType s;

	init_stack(&s);

	for (int i = 0; i < len; i++)
	{
		ch = exp[i];

		switch (ch)
		{
		case '+': case '-': case '*': case '/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) // 우선순위 비교 후 같거나 낮으면 pop
			{
				printf("%c", pop(&s));
			}
			push(&s, ch);
			break;
		case '(': 
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(')
			{
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default:
			printf("%c", ch);
			break;
		}
	}

	while (!is_empty(&s))
	{
		printf("%c", pop(&s));
	}
}

int main()
{
	char* s = "(2+3)*4+9";

	printf("중위표기수식 %s \n", s);
	printf("후위표기수식 ");
	infix_to_posfix(s);

	return 0;
}