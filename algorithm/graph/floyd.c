// 2025-02-13
// Floyd의 최단 경로 알고리즘
// 56% 12:56

#include <stdio.h>
#include <stdlib.h>

#define TRUE				1
#define FALSE				0
#define MAX_VERTICES		100
#define INF					1000L

typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];


// 출력 함수
void printA(GraphType* g)
{
	printf("======================================\n");
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			if (A[i][j] == INF)
				printf("  * ");
			else
				printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	printf("======================================\n");
}


void floyd(GraphType* g)
{
	// init
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			A[i][j] = g->weight[i][j];
		}
	}
	printA(g);										// 초기 상태 출력


	for (int k = 0; k < g->n; k++)					// 중간 경유지
	{
		for (int i = 0; i < g->n; i++)				// 출발 노드
		{
			for (int j = 0; j < g->n; j++)			// 도착 노드
			{
				if (A[i][k] + A[k][j] < A[i][j])	// 만약 경유지를 거쳐가는 게 더 가중치가 낮다면
					A[i][j] = A[i][k] + A[k][j];
			}
		}

		printA(g);									// 단계별 결과 출력
	}
}

int main()
{
	GraphType g = { 7,
   {{   0,   7,   INF, INF, 3,   10,  INF   },
	{   7,   0,   4,   10,  2,   6,   INF   },
	{   INF, 4,   0,   2,   INF, INF, INF   },
	{   INF, 10,  2,   0,   11,  9,   4     },
	{   3,   2,   INF, 11,  0,   INF, 5     },
	{   10,  6,   INF, 9,   INF, 0,   INF   },
	{   INF, INF, INF, 4,   5,   INF, 0     }} };

	floyd(&g);

	return 0;
}