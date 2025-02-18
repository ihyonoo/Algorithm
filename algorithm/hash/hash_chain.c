// 2025-02-18
// Hash chain: 연결 리스트를 이용하여 collision 처리

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE	7			// 가능하면 소수로 크기를 정해서 collision 최소화

typedef struct {
	int key;
}element;

typedef struct list {
	element item;
	struct linst* link;
}list;

list* hash_table[TABLE_SIZE];


// 제산 함수를 이용하여 해쉬값 구하기
int hash_function(int key)
{
	return key % TABLE_SIZE;
}


// add
void hash_chain_add(element item, list* ht[])
{
	// 해쉬 값 계산
	int hash_value = hash_function(item.key);

	list* ptr;
	list* node_before = NULL;
	list* node = ht[hash_value];

	// 해쉬값 인덱스에 해당하는 연결리스트를 검색
	for (; node; node_before = node, node = node->link) 
	{
		if (node->item.key == item.key)
		{
			printf("dupe key not allowed\n");
			return;
		}
	}

	// 새로운 노드 생성
	ptr = (list*)malloc(sizeof(list));
	ptr->item = item;
	ptr->link = NULL;

	// 연결리스트에 노드 추가
	if (node_before)
	{
		node_before->link = ptr;	// 기존 노드가 있는 경우 새 노드를 끝에 연결
	}
	else 
	{
		ht[hash_value] = ptr;		// 기존 노드가 없는 경우 테이블 슬롯에 직접 연결
	}
}

// search
void hash_chain_search(element item, list* ht[])
{
	struct list* node;

	int hash_value = hash_function(item.key);

	for (node = ht[hash_value]; node; node = node->link)
	{
		if (node->item.key == item.key)
		{
			fprintf(stderr, "탐색 %d 성공 \n", item.key);
			return;
		}
	}
	printf("not found\n");
}

// print
void hash_chain_print(list* ht[])
{
	list* node;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		printf("[%d] ->", i);
		for (node = ht[i]; node; node = node->link)
		{
			printf("%d ->", node->item.key);
		}
		printf("\n");
	}
	printf("\n");
}



int main()
{
	int data[5] = { 8, 1, 9, 6, 13 };
	element e;

	for (int i = 0; i < 5; i++)
	{
		e.key = data[i];
		hash_chain_add(e, hash_table);
		hash_chain_print(hash_table);
	}
	for (int i = 0; i < 5; i++)
	{
		e.key = data[i];
		hash_chain_search(e, hash_table);

	}

	return 0;
}