#include <stdio.h>

void hanoi_tower(int n, char a, char b, char c)
{
	if (n == 1)
	{
		printf("원판 1 : %c -> %c \n", a, c);
	}
	else
	{
		hanoi_tower(n - 1, a, c, b); //맨 밑 제외 B로 이동
		printf("원판 %d : %c -> %c \n", n, a, c); // A에 남은 마지막 남은 원반을 C로 이동
		hanoi_tower(n - 1, b, a, c);  //B의 원반을 모두 C로 이동
	}
}

int main()
{
	hanoi_tower(3, 'A', 'B', 'C');

	return 0;
}