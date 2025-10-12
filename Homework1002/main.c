#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��� ����ü ���� (���� �ڷ���)
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// �� ��带 �����Ͽ� ��ȯ�ϴ� �Լ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("�޸� �Ҵ� ����");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ���� Ž�� Ʈ���� ��带 �����ϴ� �Լ� (����� ����)
// �ߺ��� ���� �������� �ʽ��ϴ�.
Node* insertNode(Node* root, int data) {
    // Ʈ���� ����ְų�, ���� ��ġ�� ã���� ���
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        // �����Ͱ� ������ ���� ����Ʈ���� �̵�
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data) {
        // �����Ͱ� ũ�� ������ ����Ʈ���� �̵�
        root->right = insertNode(root->right, data);
    }
    // �����Ͱ� �̹� ����(�ߺ�)�ϸ� �ƹ��͵� ���� �ʰ� root ��ȯ

    return root;
}

// �迭���� ��ǥ ���� ���� Ž���ϴ� �Լ�
// target: ã���� �ϴ� ����
// arr: Ž���� �迭
// size: �迭�� ũ��
int linearSearch(int target, const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        // �迭�� ���� ��ҿ� ��ǥ ���� ��
        if (arr[i] == target) {
            printf("��ǥ �� %d�� �迭�� %d��° ��ġ���� ã�ҽ��ϴ�.\n", target, i);
            return i; // ã������ �ش� �ε��� ��ȯ
        }
    }
    printf("��ǥ �� %d�� �迭�� �������� �ʽ��ϴ�.\n", target);
    return -1; // ã�� �������� -1 ��ȯ
}

// ���� Ž�� Ʈ������ ��ǥ ���� ã�� �Լ�
Node* searchBST(Node* root, int target) {
    // 1. Ʈ���� ��� �ְų� (NULL), ��带 ã���� ���
    if (root == NULL || root->data == target) {
        return root;
    }

    // 2. ��ǥ ���� ���� ��庸�� ������ ���� ����Ʈ�� Ž��
    if (target < root->data) {
        return searchBST(root->left, target);
    }
    // 3. ��ǥ ���� ���� ��庸�� ũ�� ������ ����Ʈ�� Ž��
    else {
        return searchBST(root->right, target);
    }
}

// �޸� ���� �Լ�
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    // ���� �ʱ�ȭ: ���� �ð��� �õ�� ����Ͽ� �Ź� �ٸ� ������ ����
    srand((unsigned int)time(NULL));

    Node* root = NULL; // ���� Ž�� Ʈ���� ��Ʈ ��� (�ʱ�: NULL)
    int random_numbers[100]; // 100���� ������ ������ �迭
    int count = 0; // ������ ���Ե�(�ߺ� ����) ����� ����
    const int ARRAY_SIZE = 100;

    // �ð� ������ ���� �ʿ��� ����
    clock_t start, finish;
    double duration;

    // 1. 0~1000 ������ ���ڸ� �������� 100�� �����Ͽ� �迭�� ����
    for (int i = 0; i < 100; i++) {
        // rand() % 1001 : 0���� 1000������ ���� ����
        int num = rand() % 1001;
        random_numbers[i] = num;
        // printf("%d ", num); // ������ ������ Ȯ���ϰ� ������ �ּ� ����
    }

    // 2. ������ ������ ���� Ž�� Ʈ���� ����
    for (int i = 0; i < 100; i++) {
        Node* old_root = root;
        // 2. �ش� �ڷḦ ����Ž��Ʈ���� ���� (�ߺ��� �ڵ� ���ܵ�)
        root = insertNode(root, random_numbers[i]);

        // �ߺ��� �ƴ� ���ο� ��尡 ���ԵǾ����� Ȯ��
        if (root != old_root || i == 0 || (root->data != random_numbers[i] && random_numbers[i] < root->data && root->left && root->left->data == random_numbers[i]) || (random_numbers[i] > root->data && root->right && root->right->data == random_numbers[i])) {
            // ��Ȯ�� �ߺ� Ȯ���� �����ϹǷ� �ܼ��ϰ� ī��Ʈ (���� ��ȸ ����� Ȯ�� ����)
            // ���� ���������� �ߺ��� üũ�ϴ� ������ �Լ��� ����ؾ� ��Ȯ��. ���⼭�� ������ ī��Ʈ ��ŵ
            if (i == 0 || root != old_root) {
                count++;
            }
        }
    }

    // 3-1. ������ ���ڸ� ���, �迭���� Ž�� ����
    // �迭 ������ '������ �ε���'�� ���� (0���� 99����)
    int randomIndex = rand() % ARRAY_SIZE; // ARRAY_SIZE�� 100

    // ���õ� ���� �ε����� '��'�� ��ǥ ������ ����
    start = clock();
    int target1 = random_numbers[randomIndex];

    printf("�迭�� ������ �ε��� (%d)�� �ִ� �� (%d)�� ��ǥ�� Ž���մϴ�.\n",
        randomIndex, target1);
    linearSearch(target1, random_numbers, ARRAY_SIZE);

    finish = clock();
    duration = (double)(finish - start)/ CLOCKS_PER_SEC;
    printf("�迭�� Ž���ϴ� ���� �ɸ� �ð���, %f���Դϴ�.\n", duration);

    // 3-2. Ž���� ���� ���� ����, ���� Ž�� Ʈ������ Ž�� ����
    start = clock();

    printf("\n���� Ž�� Ʈ�� Ž������ �ش� ��(%d)�� ��ǥ�� Ž���մϴ�.\n", target1);
    Node* resultNode = searchBST(root, target1);
    printf("��ǥ �� %d�� ���� Ž�� Ʈ������ ã�ҽ��ϴ�. (��� �ּ�: %p)\n",
            target1, (void*)resultNode);

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("����Ž��Ʈ���� Ž���ϴ� ���� �ɸ� �ð���, %f���Դϴ�.\n\n",duration);

    // �������� �Ҵ�� �޸� ����
    freeTree(root);

    return 0;
}