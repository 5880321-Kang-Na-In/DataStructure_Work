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
struct Node* makeNewNode(int num)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	if (temp == NULL) exit(1);
	temp->data = num;
	temp->leftNode_add = NULL;
	temp->rightNode_add = NULL;
	return temp;
}

// 이진탐색트리 배열의 첫 수를 기준으로 두고,
// 작으면 기준 수의 왼쪽 노드 주소에 추가, 새 노드 생성
// 크면 오른쪽에
struct Node* makeBST(int arr[], struct Node*Root)
{
	// 반복문에 넣어서 if로 i==0인지 계속 확인하지 말고 한 번에 쓰자
	Root->data = arr[0];
	for (int i = 1; i < ARR_SIZE; i++)
	{
		// 밑에서 Root=Root-> ;식으로, 변수 Root로 받은 거의 내용을 바꿔버리면, 진짜 트리의 루트 유지가 안 되니까
		// 인덱스를 새로 바꿀 때마다 진짜 트리의 루트에서부터 비교해서 밑의 내용을 수행하게
		// Q. 근데 이러면, Root도 Head가 줄줄이 연결해 가리키는 걸, 똑같이 가리킬 수 있나? return을 Root로 하니까,
		struct Node* Head = Root;
		while (1)
		{
			// 루트랑 비교해서 작은지 큰지 봐야 함
			// 작은지 큰지 비교한 후 주소가 눌이면 새 노드 생성해서 연결
			// 루트보다 수가 작다면
			if (arr[i] < Head->data)
			{
				// 왼쪽 주소에 연결된 게 없다면
				if (Head->leftNode_add == NULL)
				{
					// 연결하고 초기화
					// Q. 이 반복문 내에서 실행을 하면, 변수 이름이 겹치지 않게 이 변수를 여러번 만들어야 하니 따로 함수 작성해야 함
					// Q. 주소가 NULL일 때까지 계속 타고타고 들어가야 함 > 작은지 큰지 보고 주소를 봤는데 NULL 아니면 주소 옮겨서 continue, 왼오 말고 하는 동작은 똑같은데
					// Q. 그냥 여기서 이러지 말고, 루트 생성 함수를 새 노드 생성 함수로 바꿔쓸까
					// 임시 주소에 저장한 뒤, 주소를 지정하는 변수를 해제해서, 반복문 돌아갈 때마다 계속 사용할 수 있게 하자. 그러려면 temp=NULL
					struct Node* temp = makeNewNode(arr[i]);
					Head->leftNode_add = temp;
					temp = NULL;
					break;
					// Q. 다음 반복을 위해 Root로 주소 지정해줄 필요 있나?
				}
				else
				{
					Head = Head->leftNode_add;
					continue;
				}
			}
			// 루트보다 수가 크다면
			else
			{
				if (Head->rightNode_add == NULL)
				{
					struct Node* temp = makeNewNode(arr[i]);
					Head->rightNode_add = temp;
					temp = NULL;
					break;
				}
				else
				{
					Head = Head->rightNode_add;
					continue;
				}
			}
		}
	}
	return Root;
}

// 배열에서 탐색 / 탐색 횟수를 반환
int srchArray(int num, int arr[])
{
	int count = 0;
	for (int i = 0; i < ARR_SIZE; i++)
	{
		// 비교할 거니까 미리 횟수 추가
		count++;
		if (num == arr[i])
		{
			break;
		}
	}
	return count;
}

// BST 이진탐색트리에서 탐색
// 해당 노드의 수와 비교해 : (큰지 작은지) 같은지 / 크거나 작다면, 해당하는 주소의 노드로 옮겨서 다시 반복
int srchBST(int num, struct Node*Root)
{
	int count = 0;
	// 탐색하는 노드의 주소가 끝 NULL 이 나올 때까지 비교해야, NULL이 나오면 멈춰야 함
	while (1)
	{
		count++;
		if (num == Root->data)
		{
			break;
		}
		else
		{
			// num이 더 커
			if (num > Root->data)
			{
				if (Root->rightNode_add == NULL) break;
				Root = Root->rightNode_add;
			}
			// num이 더 작아
			else
			{
				if (Root->leftNode_add == NULL) break;
				Root = Root->leftNode_add;
			}
		}
	}
	return count;
}

// AVL에서 탐색
int srchAVL(int num, struct Node*Root)
{
	int count = 0;
	return count;
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

	// 트리 선언 및 초기화
	struct Node* Root1_BST = makeNewNode(arr1[0]);
	// 이진탐색트리에 저장하려면
	// 일단 맨 처음은 루트에, 헤드에 저장해
	// 그 다음 수는 루트와 비교 > 루트보다 크면, 루트의 오른쪽주소를 보고, 없으면 추가 / 있으면 그 주소로 이동해 다시 비교
	// 작으면 왼쪽주소
	// Q. 반환 없이 함수 실행이 더 좋을텐데 그러려면 포인터에 대한 포인터 어쩌구가 복잡해서
	Root1_BST = makeBST(arr1, Root1_BST);
	struct Node* Root1_AVL = makeNewNode(arr1[0]);

	struct Node* Root2_BST = makeNewNode(arr2[0]);
	Root2_BST = makeBST(arr2, Root2_BST);
	struct Node* Root2_AVL = makeNewNode(arr2[0]);

	struct Node* Root3_BST = makeNewNode(arr3[0]);
	Root3_BST = makeBST(arr3, Root3_BST);
	struct Node* Root3_AVL = makeNewNode(arr3[0]);

	struct Node* Root4_BST = makeNewNode(arr4[0]);
	Root4_BST = makeBST(arr4, Root4_BST);
	struct Node* Root4_AVL = makeNewNode(arr4[0]);


	// 탐색
	// 탐색 변수 선언 및 초기화
	// 횟수+=횟수; 평균=횟수/1000; 을 하고
	int count1_Ar = 0;
	int count2_Ar = 0;
	int count3_Ar = 0;
	int count4_Ar = 0;

	int count1_BST = 0;
	int count2_BST = 0;
	int count3_BST = 0;
	int count4_BST = 0;

	int count1_AVL = 0;
	int count2_AVL = 0;
	int count3_AVL = 0;
	int count4_AVL = 0;

	// 탐색을 진행
	// 왜 밑에처럼 쓰면, count1_Ar은 초기화되지 않는다고 뜨는가
	//int count1_Ar, count1_BST, count1_AVL = 0;
	for (int i = 0; i < 1000; i++)
	{
		int num = rand() % 10001;

		count1_Ar += srchArray(num,arr1);
		count2_Ar += srchArray(num, arr2);
		count3_Ar += srchArray(num, arr3);
		count4_Ar += srchArray(num, arr4);

		count1_BST += srchBST(num, Root1_BST);
		count2_BST += srchBST(num, Root2_BST);
		count3_BST += srchBST(num, Root3_BST);
		count4_BST += srchBST(num, Root4_BST);

		count1_AVL += srchAVL(num, Root1_AVL);
		count2_AVL += srchAVL(num, Root2_AVL);
		count3_AVL += srchAVL(num, Root3_AVL);
		count4_AVL += srchAVL(num, Root4_AVL);
	}

	// 탐색 평균 횟수 출력
	printf("1번째 데이터 배열에서의 탐색 횟수 평균 : %lf회\n", count1_Ar / (1000.0));
	printf("1번째 이진 탐색 트리에서의 탐색 횟수 평균 : %lf회\n", count1_BST / (1000.0));
	printf("1번째 AVL에서의 탐색 횟수 평균 : %lf회\n\n", count1_AVL / (1000.0));

	printf("2번째 데이터 배열에서의 탐색 횟수 평균 : %lf회\n", count2_Ar / (1000.0));
	printf("2번째 이진 탐색 트리에서의 탐색 횟수 평균 : %lf회\n", count2_BST / (1000.0));
	printf("2번째 AVL에서의 탐색 횟수 평균 : %lf회\n\n", count2_AVL / (1000.0));

	printf("3번째 데이터 배열에서의 탐색 횟수 평균 : %lf회\n", count3_Ar / (1000.0));
	printf("3번째 이진 탐색 트리에서의 탐색 횟수 평균 : %lf회\n", count3_BST / (1000.0));
	printf("3번째 AVL에서의 탐색 횟수 평균 : %lf회\n\n", count3_AVL / (1000.0));

	printf("4번째 데이터 배열에서의 탐색 횟수 평균 : %lf회\n", count4_Ar / (1000.0));
	printf("4번째 이진 탐색 트리에서의 탐색 횟수 평균 : %lf회\n", count4_BST / (1000.0));
	printf("4번째 AVL에서의 탐색 횟수 평균 : %lf회\n\n", count4_AVL / (1000.0));
	
	// 탐색 평균 횟수 출력
	double count_Ar = (count1_Ar + count2_Ar + count3_Ar + count4_Ar) / (4000.0);
	double count_BST = (count1_BST + count2_BST + count3_BST + count4_BST) / (4000.0);
	double count_AVL = (count1_AVL + count2_AVL + count3_AVL + count4_AVL) / (4000.0);


	printf("4종류의 데이터 배열에서의 탐색 횟수 평균 : %lf회\n", count_Ar);
	printf("4종류의 이진 탐색 트리에서의 탐색 횟수 평균 : %lf회\n", count_BST);
	printf("4종류의 AVL에서의 탐색 횟수 평균 : %lf회\n", count_AVL);
	// 해제
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