// 2025-02-12
// Prim의 MST 알고리즘 프로그램

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


int selected[MAX_VERTICES];		// 각 정점이 MST에 포함되어 있는지 여부
int distance[MAX_VERTICES];		// 최소 가중치 값 저장

// 최소 거리 정점 반환 함수
int get_min_vertex(int n)
{
	int v, i;

	// MST에 포함되지 않은 첫번째 정점을 찾음
	for (i = 0; i < n; i++)
	{
		if (!selected[i])
		{
			v = i;
			break;
		}
	}

	// 최소 거리 정점 찾기
	for (i = 0; i < n; i++)
	{
		if (!selected[i] && (distance[i] < distance[v])) // 선택 되지 않았고 v가 더 크다면
		{
			v = i;
		}
	}

	return v;
}

// Prim
void prim(GraphType* g, int s)
{
	int u, i, v;

	// 초기화
	for (u = 0; u < g->n; u++)
	{
		distance[u] = INF;
	}

	distance[s] = 0;

	for (i = 0; i < g->n; i++)
	{
		u = get_min_vertex(g->n);	// 최소 거리 정점을 찾은 후
		selected[u] = TRUE;			// MST에 포함

		if (distance[u] == INF)	return;

		printf("정점 %d 추가\n", u);
		
		for (v = 0; v < g->n; v++)	// u가 추가된 MST에 대한 distance 업데이트
		{
			if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v])
			{	
				distance[v] = g->weight[u][v];
			}
			
		}
	}
}

int main()
{ 
	GraphType g = { 7,
	{{ 0,   29,   INF,  INF,  INF,  10,   INF  },
	{  29,   0,    16,   INF,  INF,  INF,  15  },
	{  INF,  16,   0,    12,   INF,  INF,  INF },
	{  INF,  INF,  12,   0,    22,   INF,  18  },
	{  INF,  INF,  INF,  22,   0,    27,   25  },
	{  10,   INF,  INF,  INF,  27,   0,    INF },
	{  INF,  15,   INF,  18,   25,   INF,  0   }}
	};

	prim(&g, 0);

	return 0;
}

