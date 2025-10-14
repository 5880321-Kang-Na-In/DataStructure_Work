#include <stdio.h>
#include <time.h>
#define ARR_SIZE 1000

// ��忡 ���� ����ü
// ���� �ڽ� ��忡 ���� �ּ�, ������ �ڽ� ��忡 ���� �ּ�
struct Node {
	int data;
	struct Node* leftNode_add;
	struct Node* rightNode_add;
};

// 1�� �迭�� ���� ����
// 0~10000 ������ ������ ���� 1000��
void makeArray1(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = rand() % (ARR_SIZE*10+1);
}

// 2�� �迭�� ���� ����
// 0~999������ ���� 1000��
void makeArray2(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = i;
}

// 3�� �迭�� ���� ����
// 999~0������ ���� 1000��
void makeArray3(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = ARR_SIZE - (i + 1);
}

// 4�� �迭�� ���� ����
// Ư�� ������ ���� 1000��
void makeArray4(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = i * (i % 2 + 2);
}


// ����Ž��Ʈ�� �迭�� ù ���� �������� �ΰ�,
// ������ ���� ���� ���� ��� �ּҿ� �߰�, �� ��� ����
// ũ�� �����ʿ�
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

//������
//(1) 0~10000 ������ ������ ���� 1000��
//(2) 0~999���� ���ĵ� ���� 1000��
//(3) 999~0���� ���ĵ� ���� 1000��
//(4) for (int i = 0; i < 1000; i++) value[i] = i * (i % 2 + 2)�� ������ ���� 1000��
//    - �Ʒ��� ������ �� �����ͺ��� 1ȸ�� �����Ѵ�.
//    - Ž���� ������ �迭�� ����, (1) �迭, (2) ����Ž��Ʈ��, (3) AVL�� ������� �����Ѵ�.
//    - �ٽ� 0~10000 ������ 1000���� ������ �߻����� �� 3���� �ڷᱸ������ Ž���� �����Ѵ�.
//    - �迭 Ž���� ���� Ž������ �����Ѵ�.
//    - �̶� �� Ž�� �������� Ž�� Ƚ���� ����ϵ��� �Ѵ�.
//    - Ž�� Ƚ����, ��尡 ã������ ���ڿ� ��ġ�ϴ��� ���� Ƚ���̴�.
//    - �ڷḦ ã�� ���ϴ��� ������ Ž�������� Ž�� Ƚ���� ����ϵ��� �Ѵ�.
//    - �� �ڷᱸ�� �� 1000���� ���ڸ� ã�� Ž�� �������� �ڷᱸ���� ����� ����Ѵ�.