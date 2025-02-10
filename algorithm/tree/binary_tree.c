// 2025-02-07
// Tree

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

//		  15
//	  4	      20
//  1	    16	25

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

// 중위순회 LVR
void inorder(TreeNode* root)
{
	if (root != NULL)
	{
		inorder(root->left);			 //L
		printf("[%d] ", root->data); //V
		inorder(root->right);		 //R
	}
}

// 전위순회 VLR
void preorder(TreeNode* root)
{
	if (root != NULL)
	{
		printf("[%d] ", root->data); //V
		preorder(root->left);			 //L
		preorder(root->right);		 //R
	}
}

// 후위순회 LRV
void postorder(TreeNode* root)
{
	if (root != NULL)
	{
		postorder(root->left);			 //L
		postorder(root->right);		 //R
		printf("[%d] ", root->data); //V
	}
}

// 노드 개수 구하기
int get_node_count(TreeNode* node)
{
	int count = 0;

	if (node != NULL)
	{
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	}

	return count;
}

// 단말 노드 개수 구하기
int get_leaf_count(TreeNode* node)
{
	int count = 0;

	if (node != NULL)
	{
		if (node->left == NULL && node->right == NULL) // 왼쪽과 오른쪽 자식이 없다면
		{
			return 1;
		}
		else
		{
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
		}
	}

	return count;
}

// 높이 구하기
int get_height(TreeNode* node)
{
	int height = 0;

	if (node != NULL)
	{
		height = 1 + max(get_height(node->left), get_height(node->right));
	}
	
	return height;
}



int main()
{
	printf("inoder = ");
	inorder(root);
	printf("\n\n");

	printf("preoder = ");
	preorder(root);
	printf("\n\n");

	printf("postoder= ");
	postorder(root);
	printf("\n\n");


	printf("node count = %d\n", get_node_count(root));
	printf("leaf count = %d\n", get_leaf_count(root));
	printf("height = %d\n", get_height(root));

	return 0;
}