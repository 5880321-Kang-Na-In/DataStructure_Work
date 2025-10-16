#include <stdio.h>
#include <stdlib.h> // ���� �Ҵ� ���� �Լ��� ���� �ʿ�
#include <time.h>
#define ARR_SIZE 1000

// ��忡 ���� ����ü
// ���� �ڽ� ��忡 ���� �ּ�, ������ �ڽ� ��忡 ���� �ּ�
struct Node {
	int data;
	struct Node* leftNode_add;
	struct Node* rightNode_add;
	// int leftHeight, rightHeight �� �߰�?
};

// 1�� �迭�� ���� ����
// 0~10000 ������ ������ ���� 1000��
void makeArray1(int arr[])
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		int num = rand() % (ARR_SIZE * 10 + 1);
		// �ߺ� Ȯ��
		if (checkRepeat(num, arr, i) == 1)
		{
			i--;
			continue;
		}
		else
			arr[i] = num;
	}
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

// �迭 �ʱ�ȭ �� ������ ������, 
// ���� �迭�� ����Ǿ� �ִ� ������ �ߺ��� Ȯ��
// 1�� �Ǹ� �ߺ��� �ְ�, 0�� �Ǹ� �ߺ��� ����
int checkRepeat(int num, int arr[], int index)
{
	 // �迭�� ��� ���� ��
	for (int i = 0; i < index; i++)
	{
		if (num == arr[i]) return 1;
	}
	return 0;
}

// Ʈ���� ��Ʈ ��带 ����ų �ּ� ����
struct Node* makeRoot()
{
	struct Node* Root = (struct Node*)malloc(sizeof(struct Node));
	if (Root == NULL) exit(1);
	Root->data = 0;
	Root->leftNode_add = NULL;
	Root->rightNode_add = NULL;
	return Root;
}

// ����Ž��Ʈ�� �迭�� ù ���� �������� �ΰ�,
// ������ ���� ���� ���� ��� �ּҿ� �߰�, �� ��� ����
// ũ�� �����ʿ�
struct Node* makeBST(int arr[], struct Node*Root)
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		// �迭 ó���� ���ؼ�
		// Q. switch �����ε� �ɱ�
		if (i == 0)
		{
			Root->data = arr[i];
		}
		// ������ �ε����� ���ؼ�
		else
		{
			// ��Ʈ�� ���ؼ� ������ ū�� ���� ��
			// ������ ū�� ���� �� �ּҰ� ���̸� �� ��� �����ؼ� ����
			// ��Ʈ���� ���� �۴ٸ�
			if (arr[i] < Root->data)
			{

			}
			// ��Ʈ���� ���� ũ�ٸ�
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
	
	// �迭 ���� �� �ʱ�ȭ
	// Q.�̷��� ���� �� arr4�� {10000, 0, 0, ...}���� �ʱ�ȭ�ǰ�, �� ������ �迭���� �����Ⱚ�� ���°�?
	//int arr1[ARR_SIZE],arr2[ARR_SIZE], arr3[ARR_SIZE], arr4[ARR_SIZE] = { 10001 };
	int arr1[ARR_SIZE], arr2[ARR_SIZE], arr3[ARR_SIZE], arr4[ARR_SIZE];
	makeArray1(arr1);
	makeArray2(arr2);
	makeArray3(arr3);
	makeArray4(arr4);

	struct Node* Root1_BST = makeRoot();
	// ����Ž��Ʈ���� �����Ϸ���
	// �ϴ� �� ó���� ��Ʈ��, ��忡 ������
	// �� ���� ���� ��Ʈ�� �� > ��Ʈ���� ũ��, ��Ʈ�� �������ּҸ� ����, ������ �߰� / ������ �� �ּҷ� �̵��� �ٽ� ��
	// ������ �����ּ�
	// Q. ��ȯ ���� �Լ� ������ �� �����ٵ� �׷����� �����Ϳ� ���� ������ ��¼���� �����ؼ�
	Root1_BST = makeBST(arr1, Root1_BST);
	struct Node* Root1_AVL = makeRoot();

	struct Node* Root2_BST = makeRoot();
	struct Node* Root2_AVL = makeRoot();

	struct Node* Root3_BST = makeRoot();
	struct Node* Root3_Bst = makeRoot();

	struct Node* Root4_BST = makeRoot();
	struct Node* Root4_AVL = makeRoot();
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