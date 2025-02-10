// 2025-02-10
// Binary Search Tree

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

//순환적인 탐색
TreeNode* search(TreeNode* node, int key)
{
	if (node == NULL) return NULL;
	
	if (key = node->key)
	{
		return node;
	}
	else if (key < node->key)
	{
		return search(node->left, key);
	}
	else
	{
		return search(node->right, key);
	}
}

/*
// 반복적인 탐색연산 (효율성은 반복적인 탐색 연산이 훨씬 우수)
TreeNode* serch(TreeNode& node, int key)
{
	while(node != NULL)
	{
		if (key == node->key)
			return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;	// 탐색 실패
}
*/

// 노드 동적할당
TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

// insert , 비어 있을 때 까지 반복
TreeNode* insert_node(TreeNode* node, int key)
{
	if (node == NULL) return new_node(key);

	if (key < node->key)
	{
		node->left = insert_node(node->left, key);
	}
	else if (key > node->key)
	{
		node->right = insert_node(node->right, key);
	}

	return node;
}


TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
	{
		current = current->left;
	}

	return current;
}

// delete
TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) return root;

	if (key < root->key)
	{
		root->left = delete_node(root->left,key);
	}
	else if (key > root->key)
	{
		root->right = delete_node(root->right,key);
	}
	else 
	{
		// 삭제하려는 노드가 단말노드거나 하나의 서브트리만 가지고 있는 경우
		if (root->left == NULL)
		{
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		// 삭제하려는 노드가 두개의 서브트리를 가지고 있는 경우
		TreeNode* temp = min_value_node(root->right);		// 오른쪽 서브트리에서 최소값 탐색

		root->key = temp->key;								// 찾은 값을 삭제하려는 노드에 적용
		root->right = delete_node(root->right, temp->key);	// 바뀌어진 값의 원래 위치에 있던 노드를 삭제, 완성 된 서브트리들을 right에 연결
	}
	return root;
}

// 중위순회
void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}


int main()
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;

	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 40);
	root = insert_node(root, 50);
	root = insert_node(root, 60);

	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");

	if (search(root, 30) != NULL)
		printf("success\n");
	else
		printf("not found\n");

	return 0;
}