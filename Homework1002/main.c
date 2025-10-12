#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 노드 구조체 정의 (연결 자료형)
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// 새 노드를 생성하여 반환하는 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("메모리 할당 실패");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 이진 탐색 트리에 노드를 삽입하는 함수 (재귀적 구현)
// 중복된 값은 삽입하지 않습니다.
Node* insertNode(Node* root, int data) {
    // 트리가 비어있거나, 삽입 위치를 찾았을 경우
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        // 데이터가 작으면 왼쪽 서브트리로 이동
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data) {
        // 데이터가 크면 오른쪽 서브트리로 이동
        root->right = insertNode(root->right, data);
    }
    // 데이터가 이미 존재(중복)하면 아무것도 하지 않고 root 반환

    return root;
}

// 배열에서 목표 값을 선형 탐색하는 함수
// target: 찾고자 하는 숫자
// arr: 탐색할 배열
// size: 배열의 크기
int linearSearch(int target, const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        // 배열의 현재 요소와 목표 값을 비교
        if (arr[i] == target) {
            printf("목표 값 %d를 배열의 %d번째 위치에서 찾았습니다.\n", target, i);
            return i; // 찾았으면 해당 인덱스 반환
        }
    }
    printf("목표 값 %d는 배열에 존재하지 않습니다.\n", target);
    return -1; // 찾지 못했으면 -1 반환
}

// 이진 탐색 트리에서 목표 값을 찾는 함수
Node* searchBST(Node* root, int target) {
    // 1. 트리가 비어 있거나 (NULL), 노드를 찾았을 경우
    if (root == NULL || root->data == target) {
        return root;
    }

    // 2. 목표 값이 현재 노드보다 작으면 왼쪽 서브트리 탐색
    if (target < root->data) {
        return searchBST(root->left, target);
    }
    // 3. 목표 값이 현재 노드보다 크면 오른쪽 서브트리 탐색
    else {
        return searchBST(root->right, target);
    }
}

// 메모리 해제 함수
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    // 난수 초기화: 현재 시간을 시드로 사용하여 매번 다른 난수를 생성
    srand((unsigned int)time(NULL));

    Node* root = NULL; // 이진 탐색 트리의 루트 노드 (초기: NULL)
    int random_numbers[100]; // 100개의 난수를 저장할 배열
    int count = 0; // 실제로 삽입된(중복 제외) 노드의 개수
    const int ARRAY_SIZE = 100;

    // 시간 측정을 위해 필요한 변수
    clock_t start, finish;
    double duration;

    // 1. 0~1000 사이의 숫자를 무작위로 100개 생성하여 배열에 저장
    for (int i = 0; i < 100; i++) {
        // rand() % 1001 : 0부터 1000까지의 난수 생성
        int num = rand() % 1001;
        random_numbers[i] = num;
        // printf("%d ", num); // 생성된 난수를 확인하고 싶으면 주석 해제
    }

    // 2. 생성된 난수를 이진 탐색 트리에 저장
    for (int i = 0; i < 100; i++) {
        Node* old_root = root;
        // 2. 해당 자료를 이진탐색트리에 저장 (중복은 자동 제외됨)
        root = insertNode(root, random_numbers[i]);

        // 중복이 아닌 새로운 노드가 삽입되었는지 확인
        if (root != old_root || i == 0 || (root->data != random_numbers[i] && random_numbers[i] < root->data && root->left && root->left->data == random_numbers[i]) || (random_numbers[i] > root->data && root->right && root->right->data == random_numbers[i])) {
            // 정확한 중복 확인은 복잡하므로 단순하게 카운트 (중위 순회 결과로 확인 가능)
            // 실제 구현에서는 중복을 체크하는 별도의 함수를 사용해야 정확함. 여기서는 간단히 카운트 스킵
            if (i == 0 || root != old_root) {
                count++;
            }
        }
    }

    // 3-1. 임의의 숫자를 골라, 배열에서 탐색 실행
    // 배열 내에서 '랜덤한 인덱스'를 선택 (0부터 99까지)
    int randomIndex = rand() % ARRAY_SIZE; // ARRAY_SIZE는 100

    // 선택된 랜덤 인덱스의 '값'을 목표 값으로 설정
    start = clock();
    int target1 = random_numbers[randomIndex];

    printf("배열의 무작위 인덱스 (%d)에 있는 값 (%d)을 목표로 탐색합니다.\n",
        randomIndex, target1);
    linearSearch(target1, random_numbers, ARRAY_SIZE);

    finish = clock();
    duration = (double)(finish - start)/ CLOCKS_PER_SEC;
    printf("배열로 탐색하는 데에 걸린 시간은, %f초입니다.\n", duration);

    // 3-2. 탐색한 수와 같은 수를, 이진 탐색 트리에서 탐색 실행
    start = clock();

    printf("\n이진 탐색 트리 탐색에서 해당 값(%d)을 목표로 탐색합니다.\n", target1);
    Node* resultNode = searchBST(root, target1);
    printf("목표 값 %d를 이진 탐색 트리에서 찾았습니다. (노드 주소: %p)\n",
            target1, (void*)resultNode);

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("이진탐색트리로 탐색하는 데에 걸린 시간은, %f초입니다.\n\n",duration);

    // 동적으로 할당된 메모리 해제
    freeTree(root);

    return 0;
}