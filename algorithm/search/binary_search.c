// 2025-02-16
// Binary Search: 이진 탐색 프로그램
// 정렬 된 자료에서 효율적

#include <stdio.h>

// 순환적인 이진 탐색
int search_binary_recursion(int key, int low, int high, int list[])
{
	int middle;

	if (low <= high)
	{
		middle = (low + high) / 2;

		if (key == list[middle])	// 탐색 성공
			return middle;
		else if (key < list[middle])	
			return search_binary_recursion(key, low, middle - 1, list);
		else
			return search_binary_recursion(key, middle + 1, high, list);
	}

	return -1;						// 탐색 실패
}


// 반복적인 이진탐색
int search_binary(int key, int low, int high, int list[])
{
	int middle;

	while (low <= high)
	{
		middle = (low + high) / 2;

		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}

	return -1;							// 탐색 실패
}

int main()
{
	int list[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int result = search_binary_recursion(8, 0, 10, list);

	if (result == -1)
		printf("탐색 실패\n");
	else
		printf("탐색 성공: %d\n", result);

	return 0;
}