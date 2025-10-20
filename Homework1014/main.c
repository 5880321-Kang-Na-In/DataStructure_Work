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
	int height; // ���� ��带 ��Ʈ�� �ϴ� ���� Ʈ���� ����
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
struct Node* makeNewNode(int num)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	if (temp == NULL) exit(1);
	temp->data = num;
	temp->leftNode_add = NULL;
	temp->rightNode_add = NULL;
	temp->height = 1; // �� ���� ó���� ���̰� 1
	return temp;
}

// ����Ž��Ʈ�� �迭�� ù ���� �������� �ΰ�,
// ������ ���� ���� ���� ��� �ּҿ� �߰�, �� ��� ����
// ũ�� �����ʿ�
struct Node* makeBST(int arr[], struct Node*Root)
{
	// �ݺ����� �־ if�� i==0���� ��� Ȯ������ ���� �� ���� ����
	Root->data = arr[0];
	for (int i = 1; i < ARR_SIZE; i++)
	{
		// �ؿ��� Root=Root-> ;������, ���� Root�� ���� ���� ������ �ٲ������, ��¥ Ʈ���� ��Ʈ ������ �� �Ǵϱ�
		// �ε����� ���� �ٲ� ������ ��¥ Ʈ���� ��Ʈ�������� ���ؼ� ���� ������ �����ϰ�
		// Q. �ٵ� �̷���, Root�� Head�� ������ ������ ����Ű�� ��, �Ȱ��� ����ų �� �ֳ�? return�� Root�� �ϴϱ�,
		struct Node* Head = Root;
		while (1)
		{
			// ��Ʈ�� ���ؼ� ������ ū�� ���� ��
			// ������ ū�� ���� �� �ּҰ� ���̸� �� ��� �����ؼ� ����
			// ��Ʈ���� ���� �۴ٸ�
			if (arr[i] < Head->data)
			{
				// ���� �ּҿ� ����� �� ���ٸ�
				if (Head->leftNode_add == NULL)
				{
					// �����ϰ� �ʱ�ȭ
					// Q. �� �ݺ��� ������ ������ �ϸ�, ���� �̸��� ��ġ�� �ʰ� �� ������ ������ ������ �ϴ� ���� �Լ� �ۼ��ؾ� ��
					// Q. �ּҰ� NULL�� ������ ��� Ÿ��Ÿ�� ���� �� > ������ ū�� ���� �ּҸ� �ôµ� NULL �ƴϸ� �ּ� �Űܼ� continue, �޿� ���� �ϴ� ������ �Ȱ�����
					// Q. �׳� ���⼭ �̷��� ����, ��Ʈ ���� �Լ��� �� ��� ���� �Լ��� �ٲ㾵��
					// �ӽ� �ּҿ� ������ ��, �ּҸ� �����ϴ� ������ �����ؼ�, �ݺ��� ���ư� ������ ��� ����� �� �ְ� ����. �׷����� temp=NULL
					struct Node* temp = makeNewNode(arr[i]);
					Head->leftNode_add = temp;
					temp = NULL;
					break;
					// Q. ���� �ݺ��� ���� Root�� �ּ� �������� �ʿ� �ֳ�?
				}
				else
				{
					Head = Head->leftNode_add;
					continue;
				}
			}
			// ��Ʈ���� ���� ũ�ٸ�
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






// AVL ������
// �� ���� �� ū ���� ��ȯ
int my_max(int a, int b)
{
	return (a > b) ? a : b;
}

// AVL ������
// ����� ���̸� ��ȯ (NULL�� ��� 0)
int height(struct Node*Node) {
	if (Node == NULL)
		return 0;
	return Node->height;
}

// AVL ������
// ����� ���� ����(Balance Factor)�� ����Ͽ� ��ȯ
// ���� ���� = ���� ����Ʈ�� ���� - ������ ����Ʈ�� ����
int getBalance(struct Node* Node) {
	if (Node == NULL)
		return 0;
	return height(Node->leftNode_add) - height(Node->rightNode_add);
}




// ������ ȸ�� (Right Rotation) - LL Case�� ���
struct Node* rightRotate(struct Node* z) {
	struct Node* y = z->leftNode_add;
	struct Node* T3 = y->rightNode_add;

	// ȸ�� ����
	y->rightNode_add = z;
	z->leftNode_add = T3;

	// ���� ���� (�ڽ� ��� z���� ���� ����)
	z->height = my_max(height(z->leftNode_add), height(z->rightNode_add)) + 1;
	y->height = my_max(height(y->leftNode_add), height(y->rightNode_add)) + 1;

	// ���ο� ��Ʈ y ��ȯ
	return y;
}

// ���� ȸ�� (Left Rotation) - RR Case�� ���
struct Node* leftRotate(struct Node* z) {
	struct Node* y = z->rightNode_add;
	struct Node* T2 = y->leftNode_add;

	// ȸ�� ����
	y->leftNode_add = z;
	z->rightNode_add = T2;

	// ���� ���� (�ڽ� ��� z���� ���� ����)
	z->height = my_max(height(z->leftNode_add), height(z->rightNode_add)) + 1;
	y->height = my_max(height(y->leftNode_add), height(y->rightNode_add)) + 1;

	// ���ο� ��Ʈ y ��ȯ
	return y;
}

// AVL ����
// key ���� AVL Ʈ���� �����ϰ� ���ο� ��Ʈ ��带 ��ȯ (�����)
struct Node* insert(struct Node* node, int data) {
	// 1. �Ϲ� BST ���� ����
	if (node == NULL)
		return makeNewNode(data);

	if (data < node->data)
		node->leftNode_add = insert(node->leftNode_add, data);
	else if (data > node->data)
		node->rightNode_add = insert(node->rightNode_add, data);
	//else // �ߺ��� Ű�� ����
	//	return node;

	// 2. ���� ����� ���� ����
	node->height = 1 + my_max(height(node->leftNode_add), height(node->rightNode_add));

	// 3. ���� ���� ���
	int balance = getBalance(node);

	// 4. �ұ��� �߻� �� ó�� (4���� ���̽�)

	// LL Case (������ ����)
	if (balance > 1 && data < node->leftNode_add->data)
		return rightRotate(node);

	// RR Case (�������� ������)
	if (balance < -1 && data > node->rightNode_add->data)
		return leftRotate(node);

	// LR Case (������ ������): ���� ȸ�� �� ������ ȸ��
	if (balance > 1 && data > node->leftNode_add->data) {
		node->leftNode_add = leftRotate(node->leftNode_add);
		return rightRotate(node);
	}

	// RL Case (�������� ����): ������ ȸ�� �� ���� ȸ��
	if (balance < -1 && data < node->rightNode_add->data) {
		node->rightNode_add = rightRotate(node->rightNode_add);
		return leftRotate(node);
	}

	// ���� ���� �����̰ų� ȸ�� �Ŀ��� ���� ��� ��ȯ
	return node;
}






// �迭���� Ž�� / Ž�� Ƚ���� ��ȯ
int srchArray(int num, int arr[])
{
	int count = 0;
	for (int i = 0; i < ARR_SIZE; i++)
	{
		// ���� �Ŵϱ� �̸� Ƚ�� �߰�
		count++;
		if (num == arr[i])
		{
			break;
		}
	}
	return count;
}

// BST ����Ž��Ʈ������ Ž�� // AVL�� ������ ������� Ž��
// �ش� ����� ���� ���� : (ū�� ������) ������ / ũ�ų� �۴ٸ�, �ش��ϴ� �ּ��� ���� �Űܼ� �ٽ� �ݺ�
int srchTree(int num, struct Node*Root)
{
	int count = 0;
	// Ž���ϴ� ����� �ּҰ� �� NULL �� ���� ������ ���ؾ�, NULL�� ������ ����� ��
	while (1)
	{
		count++;
		if (num == Root->data)
		{
			break;
		}
		else
		{
			// num�� �� Ŀ
			if (num > Root->data)
			{
				if (Root->rightNode_add == NULL) break;
				Root = Root->rightNode_add;
			}
			// num�� �� �۾�
			else
			{
				if (Root->leftNode_add == NULL) break;
				Root = Root->leftNode_add;
			}
		}
	}
	return count;
}


void main()
{
	// ���ึ�� ���� �� ���� ����
	srand(time(NULL));
	
	// �迭 ���� �� �ʱ�ȭ
	// Q.�̷��� ���� �� arr4�� {10000, 0, 0, ...}���� �ʱ�ȭ�ǰ�, �� ������ �迭���� �����Ⱚ�� ���°�?
	//int arr1[ARR_SIZE],arr2[ARR_SIZE], arr3[ARR_SIZE], arr4[ARR_SIZE] = { 10001 };
	int arr1[ARR_SIZE], arr2[ARR_SIZE], arr3[ARR_SIZE], arr4[ARR_SIZE];
	makeArray1(arr1);
	makeArray2(arr2);
	makeArray3(arr3);
	makeArray4(arr4);

	// Ʈ�� ���� �� �ʱ�ȭ
	// ���� Ž�� Ʈ��
	struct Node* Root1_BST = makeNewNode(arr1[0]);
	// ����Ž��Ʈ���� �����Ϸ���
	// �ϴ� �� ó���� ��Ʈ��, ��忡 ������
	// �� ���� ���� ��Ʈ�� �� > ��Ʈ���� ũ��, ��Ʈ�� �������ּҸ� ����, ������ �߰� / ������ �� �ּҷ� �̵��� �ٽ� ��
	// ������ �����ּ�
	// Q. ��ȯ ���� �Լ� ������ �� �����ٵ� �׷����� �����Ϳ� ���� ������ ��¼���� �����ؼ�
	Root1_BST = makeBST(arr1, Root1_BST);

	// AVL Ʈ�� : ���� Ž�� Ʈ��ó�� ���� �ϳ��� �����ϸ鼭 ȸ�� ���� ����
	struct Node* Root1_AVL = NULL;
	for (int i = 0; i < ARR_SIZE; i++) {
		Root1_AVL = insert(Root1_AVL, arr1[i]);
	}

	struct Node* Root2_BST = makeNewNode(arr2[0]);
	Root2_BST = makeBST(arr2, Root2_BST);
	struct Node* Root2_AVL = NULL;
	for (int i = 0; i < ARR_SIZE; i++) {
		Root2_AVL = insert(Root2_AVL, arr2[i]);
	}

	struct Node* Root3_BST = makeNewNode(arr3[0]);
	Root3_BST = makeBST(arr3, Root3_BST);
	struct Node* Root3_AVL = NULL;
	for (int i = 0; i < ARR_SIZE; i++) {
		Root3_AVL = insert(Root3_AVL, arr3[i]);
	}

	struct Node* Root4_BST = makeNewNode(arr4[0]);
	Root4_BST = makeBST(arr4, Root4_BST);
	struct Node* Root4_AVL = NULL;
	for (int i = 0; i < ARR_SIZE; i++) {
		Root4_AVL = insert(Root4_AVL, arr4[i]);
	}


	// Ž��
	// Ž�� ���� ���� �� �ʱ�ȭ
	// Ƚ��+=Ƚ��; ���=Ƚ��/1000; �� �ϰ�
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

	// Ž���� ����
	// �� �ؿ�ó�� ����, count1_Ar�� �ʱ�ȭ���� �ʴ´ٰ� �ߴ°�
	//int count1_Ar, count1_BST, count1_AVL = 0;
	for (int i = 0; i < 1000; i++)
	{
		int num = rand() % 10001;

		count1_Ar += srchArray(num,arr1);
		count2_Ar += srchArray(num, arr2);
		count3_Ar += srchArray(num, arr3);
		count4_Ar += srchArray(num, arr4);

		count1_BST += srchTree(num, Root1_BST);
		count2_BST += srchTree(num, Root2_BST);
		count3_BST += srchTree(num, Root3_BST);
		count4_BST += srchTree(num, Root4_BST);

		count1_AVL += srchTree(num, Root1_AVL);
		count2_AVL += srchTree(num, Root2_AVL);
		count3_AVL += srchTree(num, Root3_AVL);
		count4_AVL += srchTree(num, Root4_AVL);
	}

	// Ž�� ��� Ƚ�� ���
	printf("1��° ������ �迭������ Ž�� Ƚ�� ��� : %lfȸ\n", count1_Ar / (1000.0));
	printf("1��° ���� Ž�� Ʈ�������� Ž�� Ƚ�� ��� : %lfȸ\n", count1_BST / (1000.0));
	printf("1��° AVL������ Ž�� Ƚ�� ��� : %lfȸ\n\n", count1_AVL / (1000.0));

	printf("2��° ������ �迭������ Ž�� Ƚ�� ��� : %lfȸ\n", count2_Ar / (1000.0));
	printf("2��° ���� Ž�� Ʈ�������� Ž�� Ƚ�� ��� : %lfȸ\n", count2_BST / (1000.0));
	printf("2��° AVL������ Ž�� Ƚ�� ��� : %lfȸ\n\n", count2_AVL / (1000.0));

	printf("3��° ������ �迭������ Ž�� Ƚ�� ��� : %lfȸ\n", count3_Ar / (1000.0));
	printf("3��° ���� Ž�� Ʈ�������� Ž�� Ƚ�� ��� : %lfȸ\n", count3_BST / (1000.0));
	printf("3��° AVL������ Ž�� Ƚ�� ��� : %lfȸ\n\n", count3_AVL / (1000.0));

	printf("4��° ������ �迭������ Ž�� Ƚ�� ��� : %lfȸ\n", count4_Ar / (1000.0));
	printf("4��° ���� Ž�� Ʈ�������� Ž�� Ƚ�� ��� : %lfȸ\n", count4_BST / (1000.0));
	printf("4��° AVL������ Ž�� Ƚ�� ��� : %lfȸ\n\n", count4_AVL / (1000.0));
	
	// Ž�� ��� Ƚ�� ���
	double count_Ar = (count1_Ar + count2_Ar + count3_Ar + count4_Ar) / (4000.0);
	double count_BST = (count1_BST + count2_BST + count3_BST + count4_BST) / (4000.0);
	double count_AVL = (count1_AVL + count2_AVL + count3_AVL + count4_AVL) / (4000.0);


	printf("4������ ������ �迭������ Ž�� Ƚ�� ��� : %lfȸ\n", count_Ar);
	printf("4������ ���� Ž�� Ʈ�������� Ž�� Ƚ�� ��� : %lfȸ\n", count_BST);
	printf("4������ AVL������ Ž�� Ƚ�� ��� : %lfȸ\n", count_AVL);
	// ����
}