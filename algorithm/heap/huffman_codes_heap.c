// 2025-02-11
// 최소 히프를 사용한 허프만 코드 프로그램

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT		200

typedef struct TreeNode {
	int weight; // 빈도 수 (가중치)
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct {
	TreeNode* ptree; 
	char ch;
	int key; // 빈도수
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;



HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

// 최소 힙 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while ((child <= h->heap_size))
	{
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
		{
			child++;
		}

		if (temp.key < h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}

// 이진 트리 생성 함수 (두 개의 노드를 합쳐 새로운 노드 생성)
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	
	node->left = left;
	node->right = right;

	return node;
}

// 이진 트리 제거 함수 (재귀적으로 메모리 해제)
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;

	destroy_tree(root->left);
	destroy_tree(root->right);

	free(root);
}

int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{
	if (root->left) // 왼쪽 자식 1
	{
		codes[top] = 1; 
		print_codes(root->left, codes, top + 1);
	}

	if (root->right) // 오른쪽 자식 0
	{
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	if (is_leaf(root)) // 단말 노드면
	{
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

// 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n)
{
	TreeNode* node,* x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);

	// 각 문자를 최소 힙에 삽입
	for (int i = 0; i < n; i++)
	{
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	// 가장 작은 두 개의 노드를 꺼내어 병합
	for (int i = 1; i < n; i++)
	{
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);

		x = make_tree(e1.ptree, e2.ptree); // 새롭게 생성한 노드

		e.key = x->weight = e1.key + e2.key; // 빈도 수 +

		e.ptree = x;
		printf("%d + %d -> %d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}


	// 최종 트리에서 허프만 코드 출력
	e = delete_min_heap(heap);
	print_codes(e.ptree, codes, top);
	destroy_tree(e.ptree);

	free(heap);
}

int main()
{
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6 ,8, 12, 15 };
	
	huffman_tree(freq, ch_list, 5);

	return 0;
}