// 2025-02-18
// AVL트리 프로그램: 이진 탐색 트리의 균형 유지

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char word[20];
	char mean[20];
}element;

typedef struct AvlNode {
	element data;
	struct AvlNode* left_child, *right_child;
}AvlNode;

AvlNode* root;

// max값 반환
int maxs(int a, int b)
{
	int result = 0;

	if (a > b) {
		result = a;
	}
	else if (b > a) {
		result = b;
	}

	return result;
}


// 트리의 높이를 반환
int get_height(AvlNode* node)
{
	int height = 0;

	if (node != NULL)
	{
		height = 1 + maxs(get_height(node->left_child), get_height(node->right_child));
	}

	return height;
}

// 노드 균형을 판단하기 위한 함수
int get_height_diff(AvlNode* node)
{
	if (node == NULL)  return 0;//서브트리가 없기 떄문에 높이차도 0
		
	return get_height(node->left_child) - get_height(node->right_child);
}

// LL 회전
AvlNode* rotate_LL(AvlNode* parent)
{
	//부모 노드의 왼쪽 자식을 자식노드로 설정
	AvlNode* child = parent->left_child;

	//부모 노드의 왼쪽 자식을 자식 노드의 오른쪽 자식으로 설정
	parent->left_child = child->right_child;

	//자식 노드의 오른쪽 자식을 기존에 부모 노드 parent로 설정
	child->right_child = parent;

	//자식 노드를 새로운 부모 노드로 반환
	return  child;
}

// RR회전
AvlNode* rotate_RR(AvlNode* parent)
{
	//부모 노드의 오른쪽 자식을 자식노드로 설정
	AvlNode* child = parent->right_child;
	//부모 노드의 오른쪽 자식을 자식 노드의 왼쪽 자식으로 설정
	parent->right_child = child->left_child;
	//자식 노드의 왼쪽 자식을 부모 노드로 설정
	child->left_child = parent;

	//자식 노드를 새로운 부모 노드로 반환
	return  child;
}

// LR회전
AvlNode* rotate_LR(AvlNode* parent)
{
	//부모 노드의 왼쪽 자식을 자식노드로 설정
	AvlNode* child = parent->left_child;

	//자식 노드에 대해 RR회전을 수행
	parent->left_child = rotate_RR(child);

	//부모 노드에 대해 LL회전을 수행하고 새로운 루트를 반환
	return rotate_LL(parent);
}

// RL회전
AvlNode* rotate_RL(AvlNode* parent)
{
	//부모 노드의 오른쪽 자식을 자식노드로 설정
	AvlNode* child = parent->right_child;

	//자식 노드에 대해 LL회전을 수행
	parent->right_child = rotate_LL(child);

	//부모 노드에 대해 RR회전을 수행하고 새로운 루트를 반환
	return rotate_RR(parent);
}

AvlNode* rebalance(AvlNode** node)
{
	//balance factor (높이차를 구하기)
	int height_diff = get_height_diff(*node);
	// height_diff > 1 =>>> 왼쪽트리가 더 무겁다
	// height_diff < 1 =>>> 오른쪽트리가 더 무겁다

	if (height_diff > 1)
	{
		//		 LL
		//		/
		//	   /
		//			LR
		//			  \
		//			   \
		//왼쪽 자식의 높이 차이가 양수인 경우
		if (get_height_diff((*node)->left_child) > 0) //L
		{
			*node = rotate_LL(*node); //LL
		}
		else 
		{
			*node = rotate_LR(*node);//LR
		}
	}
	else if (height_diff < -1) { //RR RL
		//오른쪽 자식의 높이 차이가 음수인 경우에는 RR을 수행
		if (get_height_diff((*node)->right_child) < 0)
		{
			*node = rotate_RR(*node);
		}
		else
		{
			*node = rotate_RL(*node);
		}
	}

	return *node; // 균형을 잡은 노드를 반환
}

AvlNode* avl_add(AvlNode** root, element new_key)
{
	if (*root == NULL)											// 트리가 비어있는 경우
	{		
		*root = (AvlNode*)malloc(sizeof(AvlNode));
		if (*root == NULL) 
		{
			printf("memory allocation failure\n");
			exit(1);
		}

		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;

	}
	else if (strcmp(new_key.word, (*root)->data.word) > 0)		// 새로운 키가 현재 노드의 키보다 큰 경우에는 왼쪽 서브트리에 추가
	{
		
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);		// add
		(*root) = rebalance(root);											// rebalance
	}
	else if (strcmp(new_key.word, (*root)->data.word) < 0)		// 새로운 키가 현재 노드의 키보다 작은 경우에는 오른쪽 서브트리에 추가
	{
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);	// add
		(*root) = rebalance(root);											// rebalance
	}
	else 
	{															//duplicated key
		printf("중복키 오류\n");
		exit(1);
	}

	return *root;

}

void display(AvlNode* root)
{

	if (root != NULL)
	{

		printf("%s - %s ", root->data.word, root->data.mean);

		display(root->left_child);

		display(root->right_child);
	}
}

AvlNode* avl_search(AvlNode* node, element key)
{
	if (node == NULL)
	{
		return NULL;
	}

	
	if (strcmp(key.word, node->data.word) == 0)			// 탐색 성공
	{
		return node;
	}
	else if (strcmp(key.word, node->data.word) > 0)		// key > data : 왼쪽 서브트리 탐색
	{
		return avl_search(node->left_child, key);
	}
	else if (strcmp(key.word, node->data.word) < 0)		// key < data : 오른쪽 서브트리 검색
	{
		return avl_search(node->right_child, key);
	}
}

int main()
{
	FILE* fp;
	char flag;
	element tmp;
	AvlNode* result;

	fp = fopen("AVL_5data.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%c", &flag);

		if (flag == 'i') {
			fscanf(fp, "%s %s", tmp.word, tmp.mean);
			printf("삽입 : %s %s\n", tmp.word, tmp.mean);
			avl_add(&root, tmp);

		}
		else if (flag == 's') {
			fscanf(fp, "%s", tmp.word);
			strcpy(tmp.mean, "");
			result = avl_search(root, tmp);
			printf("탐색결과 : %s - %s\n", result->data.word, result->data.mean);
		}
		else {
			printf("inavalid flag\n");

		}

	}
	printf("\n< AVL 트리 출력 > \n");
	display(root);

	fclose(fp);
	return 0;
}