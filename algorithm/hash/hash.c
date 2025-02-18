// 2025-02-18
// Hash 자료구조 구현 프로그램
// 제산함수와 선형조사법 이용

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE				10
#define TABLE_SIZE				13									// 가능하면 소수로 크기를 정해서 collision 최소화
#define empty(item)				(strlen(item.key) == 0)				// 해쉬 테이블에 해당 슬롯이 비어있는지를 체크하는 메크로
#define equal(item1, item2)		(!strcmp(item1.key, item2.key))		// 두 키가 동일한지 비교하는 매크로


typedef struct {
	char key[KEY_SIZE];
}element;

element hash_table[TABLE_SIZE];

// init hash table 
void init_table(element ht[])
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key[0] = 0;
	}
}

// 제산함수를 이용한 해쉬값 구하기
int transform(char* key)
{
	int number = 0; //key의 asicc 코드값을 저장

	while (*key)
	{
		number = number + *key++; //각 문자의 아스키 값을 누적해서 계산
	}

	return number;
}

int hash_function(char* key)
{
	//key를 정수로 변환한 다음 테이블 크기로 나누어서 slot 번호 확정
	return transform(key) % TABLE_SIZE;
}
///////////////////////////////////////////////

// add
void hash_lp_add(element item, element ht[])
{
	// hash 값 계산
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	// collision check
	while (!empty(ht[i]))
	{
		printf("collition detected : %d\n", i);

		// 1. hash table에 dupe key는 허용하지 않음
		if (equal(item, ht[i]))
		{
			printf("dupe key not allowed\n");
			exit(1);
		}

		// 2. liner probing, 선형 조사법
		i = (i + 1) % TABLE_SIZE;

		// 3. hash table의 끝까지 갔다면 (full)
		//hash_value = 9   i =9
		if (i == hash_value)
		{
			printf("hahs table is full\n");
			exit(1);
		}
	}

	ht[i] = item;	// add
}

// search
void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	//collision check
	while (!empty(ht[i]))
	{
		//printf("collition detected : %d\n", i);

		// 1. hash table에 dupe key는 허용하지 않음, 탐색 성공
		if (equal(item, ht[i]))
		{
			printf("탐색 [%d] %s\n", i, item.key);
			return;
		}

		// 2. liner probing, 선형 조사법
		i = (i + 1) % TABLE_SIZE;

		// 3. hash table의 끝까지 갔는데도 없으면
		//hash_value = 9   i =9
		if (i == hash_value)
		{
			printf("key not found in hash table\n");
			return;
		}
	}

	printf("key not found in hash table\n");
}

// print
void hash_lp_print(element ht[])
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		printf("[%d] %s\n", i, ht[i].key);
	}

	printf("\n\n");
}


int main()
{
	char* s[7] = { "do", "for", "if", "case", "else", "return", "function" };
	element e;

	init_table(hash_table);

	for (int i = 0; i < 7; i++)
	{
		strcpy(e.key, s[i]);
		hash_lp_add(e, hash_table);
		hash_lp_print(hash_table);
	}
	for (int i = 0; i < 7; i++)
	{
		strcpy(e.key, s[i]);
		hash_lp_search(e, hash_table);

	}
	return 0;
}

