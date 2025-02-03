#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE	100000000 //1억개까지 가능
#define swap(a, b, temp) { temp = a; a = b; b = temp; } // swap(a,p,temp) : a와 b값 서로 스왑


/////////////////선택정렬////////////////////
void selection_sort(int* arr, int count)
{
	int i, j, least;
	int temp;

	for (i = 0; i < count - 1; i++) //범위가 count - 1 인 이유 : 최악의 경우에도 크기 - 1번 swap하기 때문
	{
		least = i;

		for (j = i + 1; j < count; j++)	//최소값 탐색
		{
			if (arr[j] < arr[least])
			{
				least = j;
			}
		}
		swap(arr[i], arr[least], temp) //찾은 최소값 swap
	}
}


//////////////삽입정렬/////////////////////////
void insertion_sort(int* arr, int count)
{
	int i, j;
	int temp;

	for (i = 1; i < count; i++) // i보다 작은 값들은 이미 정렬되어있다.
	{
		temp = arr[i]; //temp는 비교하기 위한 key값

		for (j = i - 1; (j >= 0) && (arr[j] > temp); j--) //arr[j]값이 비교값보다 작으면 루프 실행
		{
			arr[j + 1] = arr[j];  //인덱스 앞의 값을 현재 자리로 덮어씌움
		}
		arr[j + 1] = temp;
	}
}
////////////////////////////////////

/////////////버블정렬/////////////////
void bubble_sort(int* arr, int n)
{
	int i, j;
	int temp;

	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])	//앞 뒤 비교
			{
				swap(arr[j], arr[j + 1], temp); 
			}
		}
	}
}

////////////////쉘 정렬/////////////////////////
inc_insertion_sort(int *arr, int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap)
	{
		key = arr[i];
		for (j = i - gap; j >= first && key < arr[j]; j = j - gap)
			arr[j + gap] = arr[j];
			arr[j + gap] = key;
	}
}

void shell_sort(int* arr, int count)
{
	int i, gap;
	for (gap = count / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0) //짝수보다 홀수가 더욱 효율적이기 때문에 짝수라면 홀수로 변경
		{
			gap++;
		}
		for (i = 0; i < gap; i++)
		{
			inc_insertion_sort(arr, i, count - 1, gap); //i를 기준으로 각 그룹 별로 삽입정렬 수행
		}

	}
}

///////////////////////////////합병 정렬///////////////////////////////
int sorted[MAX_SIZE];

void merge(int* arg, int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	//분할 정렬된 list의 합병
	while (i <= mid && j <= right)
	{
		if (arg[i] <= arg[j])
		{
			sorted[k++] = arg[i++];
		}
		else {
			sorted[k++] = arg[j++];
		}
	}
	
	if (i > mid) //남아 있는 레코드의 일괄 복사
	{
		for (l = j; l <= right; l++)
		{
			sorted[k++] = arg[l];
		}
	}
	else		//남아 있는 레코드의 일괄 복사
	{
		for (l = i; l <= mid; l++)
		{
			sorted[k++] = arg[l];
		}
	}

	for (l = left; l <= right; l++)
	{
		arg[l] = sorted[l];
	}
}

void merge_sort(int* arg, int left, int right)
{
	int mid;
	if (left < right) // 1개밖에 남지 않을 때까지 계속 분할
	{
		mid = (left + right) / 2; //리스트의 균등분할
		merge_sort(arg, left, mid); //왼쪽 부분리스트 정렬
		merge_sort(arg, mid + 1, right); //오른쪽 부분리스트 정렬
		merge(arg, left, mid, right); //합병
	}
}

//////////////////////퀵 정렬///////////////////////////////////////
int partition(int* arg, int left, int right) //privot을 기준으로 배열을 분할하는 함수
{
	int privot, temp = 0;
	int low, high;

	low = left;
	high = right + 1;
	privot = arg[left]; //pivot 설정

	do 
	{	
		do
		{	//privot보다 큰 값을 찾을 때까지 low를 오른쪽으로 이동
			low++;
		} while (low <= right && arg[low] < privot);

		do
		{	//privot보다 작은 값을 찾을 때까지 low를 왼쪽으로 이동
			high--;
		} while (high >= left && arg[high] > privot);

		if (low < high)
		{
			swap(arg[low], arg[high], temp);
		}
	} while (low < high);

	swap(arg[left], arg[high], temp);

	return high; 
}

void quick_sort(int* arg, int left, int right)
{
	if (left < right) //1개밖에 남지 않을 때까지 계속 분할
	{
		int q = partition(arg, left, right);
		quick_sort(arg, left, q - 1); //privot의 왼쪽 정렬
		quick_sort(arg, q + 1, right); //privot의 오른쪽 정렬
	}
}

//////////////////////////히프정렬/////////////////////////////////
void heapify(int *arr, int count, int i) {
	int parentNode = i;
	int leftChildNode = i * 2 + 1;
	int rightChildNode = i * 2 + 2;
	int temp;


	//왼쪽 자식 노드가 존재하면서 부모노드와 값 비교
	if (leftChildNode < count && arr[parentNode] < arr[leftChildNode]) {
		parentNode = leftChildNode;
	}
	//오른쪽 자식 노드가 존재하면서 부모노드와 값 비교.
	if (rightChildNode < count && arr[parentNode] < arr[rightChildNode]) {
		parentNode = rightChildNode;
	}


	//왼쪽 or 오른쪽 자식 노드 중 부모 노드보다 큰 값이 존재한 경우
	if (i != parentNode) {
		swap(arr[parentNode], arr[i], temp);
		heapify(arr, count, parentNode);
	}
}

void heap_sort(int* arr, int count) {
	int temp;

	//힙으로 변환 (최대 힙 구성)
	for (int i = count / 2 - 1; i >= 0; i--) {
		heapify(arr, count, i);
	}
	
	//힙에서 하나씩 요소를 추출하여 정렬
	for (int i = count - 1; i > 0; i--) {
		// 현재 루트(가장 큰 값)를 배열 끝으로 이동
		swap(arr[0], arr[i], temp);

		//축소된 힙에 대해 다시 정렬
		heapify(arr, i, 0);
	}
}



int main() {
	FILE* fp;
	int temp;
	int count = 0; //정수 개수
	int* arrCopy; //파일에 정수형 데이터를 담음 변수
	clock_t start, end; // 시간 측정을 위한 변수
	float timediff; //시간 결과값
	

	fp = fopen("data.txt", "r");
	if (fp == NULL) //파일이 열리지 않는다면
	{
		printf("file not found\n");
		return 1;
	}

	while (fscanf(fp, "%d", &temp) == 1) { //파일에 정수 개수 카운팅
		count++;
	}

	int* arr = (int*)malloc(sizeof(int) * count); //정수 개수만큼 동적 할당

	rewind(fp); //파일 포인터 다시 처음으로

	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d", &arr[i]); //변수에 저장
	}

	//arr복사본 생성 (각각의 시간을 측정하기 위하여)
 	arrCopy = (int*)malloc(sizeof(int) * count);
	
	//선택정렬
	for (int i = 0; i < count; i++) {
		arrCopy[i] = arr[i];
	}
	start = clock();
	selection_sort(arr, count);		
	end = clock();
	timediff = (float)(end - start) / CLOCKS_PER_SEC;
	printf("선택 정렬 시간 = %f초\n", timediff);
	

	//삽입 정렬
	for (int i = 0; i < count; i++) {
		arr[i] = arrCopy[i];
	}
	start = clock();
	insertion_sort(arr, count) ;
	end = clock();
	timediff = (float)(end - start) / CLOCKS_PER_SEC;
	printf("삽입 정렬 시간 = %f초\n", timediff);
	
	
	//버블정렬
	for (int i = 0; i < count; i++) {
		arr[i] = arrCopy[i];
	}
	start = clock();
	bubble_sort(arr, count);	
	end = clock();
	timediff = (float)(end - start) / CLOCKS_PER_SEC;
	printf("버블 정렬 시간 = %f초\n", timediff);
	
	
	//쉘정렬
	for (int i = 0; i < count; i++) {
		arr[i] = arrCopy[i];
	}
	start = clock();
	shell_sort(arr, count);			
	end = clock();
	timediff = (float)(end - start) / CLOCKS_PER_SEC;
	printf("쉘 정렬 시간 = %f초\n", timediff);
	
	
	//합병정렬
	for (int i = 0; i < count; i++) {
		arr[i] = arrCopy[i];
	}
	start = clock();
	merge_sort(arr, 0, count - 1);	
	end = clock();
	timediff = (float)(end - start) / CLOCKS_PER_SEC;
	printf("합병 정렬 시간 = %f초\n", timediff);
	
	
	//퀵정렬
	for (int i = 0; i < count; i++) {
		arr[i] = arrCopy[i];
	}
	start = clock();
	quick_sort(arr, 0, count - 1);	
	end = clock();
	timediff = (float)(end - start) / CLOCKS_PER_SEC;
	printf("퀵 정렬 시간 = %f초\n", timediff);
	
	
	//히프정렬
	for (int i = 0; i < count; i++) {
		arr[i] = arrCopy[i];
	}
	start = clock();
	heap_sort(arr, count);	
	end = clock();
	timediff = (float)(end - start) / CLOCKS_PER_SEC;
	printf("히프정렬 시간 = %f초\n", timediff);
	
	
	free(arr);
	fclose(fp);
	return 0;
}