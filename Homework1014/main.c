#include <stdio.h>
#include <time.h>
#define ARR_SIZE 1000

// 노드에 대한 구조체
// 왼쪽 자식 노드에 대한 주소, 오른쪽 자식 노드에 대한 주소
struct Node {
	int data;
	struct Node* leftNode_add;
	struct Node* rightNode_add;
};

// 1번 배열에 값을 저장
// 0~10000 사이의 무작위 정수 1000개
void makeArray1(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = rand() % (ARR_SIZE*10+1);
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


// 이진탐색트리 배열의 첫 수를 기준으로 두고,
// 작으면 기준 수의 왼쪽 노드 주소에 추가, 새 노드 생성
// 크면 오른쪽에
struct Node* makeHead()
{
	struct Node* Head = (struct Node*)malloc(sizeof(struct Node*));
	if (Head == NULL) exit(1);
	return Head;
}

void main()
{
	srand(time(NULL));
	int arr1[ARR_SIZE],arr2[ARR_SIZE], arr3[ARR_SIZE], arr4[ARR_SIZE] = { 0 };
	makeArray1(arr1);
	makeArray2(arr2);
	makeArray3(arr3);
	makeArray4(arr4);

	struct Node* Head1_BST = makeHead();
	Head1_BST->data = 2;
	printf("%d", Head1_BST->data);
	struct Node* Head1_AVL = makeHead();

	struct Node* Head2_BST = makeHead();
	struct Node* Head2_AVL = makeHead();

	struct Node* Head3_BST = makeHead();
	struct Node* Head3_Bst = makeHead();

	struct Node* Head4_BST = makeHead();
	struct Node* Head4_AVL = makeHead();
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