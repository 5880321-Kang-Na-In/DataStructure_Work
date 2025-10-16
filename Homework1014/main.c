#include <stdio.h>
#include <stdlib.h> // 동적 할당 관련 함수를 위해 필요
#include <time.h>
#define ARR_SIZE 1000

// 노드에 대한 구조체
// 왼쪽 자식 노드에 대한 주소, 오른쪽 자식 노드에 대한 주소
struct Node {
	int data;
	struct Node* leftNode_add;
	struct Node* rightNode_add;
	// int leftHeight, rightHeight 도 추가?
};

// 1번 배열에 값을 저장
// 0~10000 사이의 무작위 정수 1000개
void makeArray1(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		int num = rand() % (ARR_SIZE * 10 + 1);
		// 중복 확인
		if (checkRepeat(num, arr, i) == 1)
		{
			i--;
			continue;
		}
		else
			arr[i] = num;
	}
}

// 2번 배열에 값을 저장
// 0~999까지의 정수 1000개
void makeArray2(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = i;
}

// 3번 배열에 값을 저장
// 999~0까지의 정수 1000개
void makeArray3(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = ARR_SIZE - (i + 1);
}

// 4번 배열에 값을 저장
// 특정 조건의 정수 1000개
void makeArray4(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = i * (i % 2 + 2);
}

// 배열 초기화 중 생성한 난수가, 
// 기존 배열에 저장되어 있는 수인지 중복을 확인
// 1이 되면 중복이 있고, 0이 되면 중복이 없음
int checkRepeat(int num, int arr[], int index)
{
	 // 배열의 모든 값과 비교
	for (int i = 0; i < index; i++)
	{
		if (num == arr[i]) return 1;
	}
	return 0;
}

// 트리의 루트 노드를 가리킬 주소 생성
struct Node* makeRoot()
{
	struct Node* Root = (struct Node*)malloc(sizeof(struct Node));
	if (Root == NULL) exit(1);
	Root->data = 0;
	Root->leftNode_add = NULL;
	Root->rightNode_add = NULL;
	return Root;
}

// 이진탐색트리 배열의 첫 수를 기준으로 두고,
// 작으면 기준 수의 왼쪽 노드 주소에 추가, 새 노드 생성
// 크면 오른쪽에
struct Node* makeBST(int arr[], struct Node*Root)
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		// 배열 처음에 대해서
		// Q. switch 문으로도 될까
		if (i == 0)
		{
			Root->data = arr[i];
		}
		// 이후의 인덱스에 대해서
		else
		{
			// 루트랑 비교해서 작은지 큰지 봐야 함
			// 작은지 큰지 비교한 후 주소가 눌이면 새 노드 생성해서 연결
			// 루트보다 수가 작다면
			if (arr[i] < Root->data)
			{

			}
			// 루트보다 수가 크다면
			else
			{

			}
		}
	}
	return Root;
}

void main()
{
	srand(time(NULL));
	
	// 배열 선언 및 초기화
	// Q.이렇게 쓰면 왜 arr4만 {10000, 0, 0, ...}으로 초기화되고, 왜 나머지 배열에는 쓰레기값이 담기는가?
	//int arr1[ARR_SIZE],arr2[ARR_SIZE], arr3[ARR_SIZE], arr4[ARR_SIZE] = { 10001 };
	int arr1[ARR_SIZE], arr2[ARR_SIZE], arr3[ARR_SIZE], arr4[ARR_SIZE];
	makeArray1(arr1);
	makeArray2(arr2);
	makeArray3(arr3);
	makeArray4(arr4);

	struct Node* Root1_BST = makeRoot();
	// 이진탐색트리에 저장하려면
	// 일단 맨 처음은 루트에, 헤드에 저장해
	// 그 다음 수는 루트와 비교 > 루트보다 크면, 루트의 오른쪽주소를 보고, 없으면 추가 / 있으면 그 주소로 이동해 다시 비교
	// 작으면 왼쪽주소
	// Q. 반환 없이 함수 실행이 더 좋을텐데 그러려면 포인터에 대한 포인터 어쩌구가 복잡해서
	Root1_BST = makeBST(arr1, Root1_BST);
	struct Node* Root1_AVL = makeRoot();

	struct Node* Root2_BST = makeRoot();
	struct Node* Root2_AVL = makeRoot();

	struct Node* Root3_BST = makeRoot();
	struct Node* Root3_Bst = makeRoot();

	struct Node* Root4_BST = makeRoot();
	struct Node* Root4_AVL = makeRoot();
}

//데이터
//(1) 0~10000 사이의 무작위 정수 1000개
//(2) 0~999까지 정렬된 정수 1000개
//(3) 999~0까지 정렬된 정수 1000개
//(4) for (int i = 0; i < 1000; i++) value[i] = i * (i % 2 + 2)로 구성된 정수 1000개
//    - 아래의 과정을 위 데이터별로 1회씩 진행한다.
//    - 탐색을 진행할 배열을 각각, (1) 배열, (2) 이진탐색트리, (3) AVL에 순서대로 삽입한다.
//    - 다시 0~10000 사이의 1000개의 난수를 발생시켜 각 3개의 자료구조에서 탐색을 진행한다.
//    - 배열 탐색은 선형 탐색으로 진행한다.
//    - 이때 각 탐색 과정에서 탐색 횟수를 기록하도록 한다.
//    - 탐색 횟수란, 노드가 찾으려는 숫자와 일치하는지 비교한 횟수이다.
//    - 자료를 찾지 못하더라도 마지막 탐색까지의 탐색 횟수를 기록하도록 한다.
//    - 각 자료구조 별 1000개의 숫자를 찾는 탐색 과정에서 자료구조별 평균을 출력한다.