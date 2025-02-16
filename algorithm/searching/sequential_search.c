// 2025-02-16
// Sequential Search: 순차 탐색 프로그램

#include <stdio.h>

// 평범한 순차 탐색
int seq_search(int key, int low, int high, int list[])
{
	for (int i = 0; i <= high; i++) {		//비교 1회
		if (list[i] == key)					// 비교 2회
		{			
			return i;						// 탐색 성공	
		}							
	}

	return -1;								//탐색 실패
}


// 개선된 순차 탐색
int seq_search2(int key, int low, int high, int list[])
{
	int i;

	//핵심 아이디어는 배열에 대한 범위 체크를 하지 않는다.
	//센터널 삽입 (마커)
	list[high + 1] = key;

	for (i = low; list[i] != key; i++)		//비교 1회
		;


	if (i == (high + 1))
		return -1;
	else
		return i;
}

int main()
{
	int list[10] = { 2, 6, 1, 4, 2, 10, 500, 9, 8, 10 };

	int result = seq_search2(500, 0, 10, list);

	if (result == -1)
		printf("탐색 실패\n");
	else
		printf("탐색 성공: %d\n", result);

	return 0;
}