#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- 상수 및 전역 배열 ---
#define MAX_SIZE 2048
#define INPUT_BUFFER_SIZE 2048
char tree_array[MAX_SIZE] = { '\0', }; // 트리를 저장할 배열

// --- 스택 관련 함수 및 변수 ---
#define STACK_SIZE 1024
int stack[STACK_SIZE];
int top = -1;
int output_stack[STACK_SIZE];
int output_top = -1;

void push(int index) { if (top < STACK_SIZE - 1) stack[++top] = index; }
int pop() { return (top > -1) ? stack[top--] : 0; }
int is_empty() { return top == -1; }
void push_output(int index) { if (output_top < STACK_SIZE - 1) output_stack[++output_top] = index; }

int is_node_valid(int index) {
    return (index >= 1 && index < MAX_SIZE && tree_array[index] != '\0');
}
// -----------------------------------------------------------

// --- 파싱 함수 (이전과 동일) ---
int parse_and_insert(char** str_ptr, int index) {
    char* str = *str_ptr;

    if (index >= MAX_SIZE) return 0;

    // 1. 공백 건너뛰기
    while (*str == ' ' || *str == '\n') str++;

    // 2. '(' 확인 및 비어있는 입력 처리
    if (*str != '(') { *str_ptr = str; return 0; }
    str++; // '(' 건너뛰기

    // 3. 노드 값 확인 및 저장 또는 NULL 노드 처리
    while (*str == ' ' || *str == '\n') str++;
    if (*str == ')') {
        str++; // ')' 건너뛰기 -> NULL 노드
        *str_ptr = str;
        return 0;
    }

    // 노드 값 저장 (index 위치에)
    if (*str != '\0') {
        tree_array[index] = *str;
        str++; // 노드 값 건너뛰기
    }
    else {
        // 문자열 끝에 도달 (오류)
        *str_ptr = str;
        return 0;
    }

    // 4. 왼쪽 서브트리 파싱
    parse_and_insert(&str, 2 * index);

    // 5. 오른쪽 서브트리 파싱
    parse_and_insert(&str, 2 * index + 1);

    // 6. ')' 닫는 괄호 확인 및 건너뛰기
    while (*str == ' ' || *str == '\n') str++;
    if (*str == ')') {
        str++; // ')' 건너뛰기
    }

    *str_ptr = str;
    return 1;
}

// --- 순회 함수들 ---
void iterative_preorder_traversal() {
    printf("\npre-order: ");
    if (!is_node_valid(1)) return;

    // 반드시 스택 초기화: 이전 순회에서 사용했을 수 있으므로
    top = -1; output_top = -1;
    push(1);

    // 1. 메인 스택에서 R -> L -> Root 순으로 pop하면서 결과를 출력 스택에 저장
    while (!is_empty()) {
        int current = pop();

        // 유효한 노드인지 다시 한번 확인 (tree_array에 값이 있는지)
        if (is_node_valid(current)) {
            push_output(current); // 출력 스택에 저장 (Root)

            // R (오른쪽 자식 먼저 push, 스택에서 먼저 처리되어 L로 감)
            int left_child = 2 * current;
            if (is_node_valid(left_child)) push(left_child);

            // L (왼쪽 자식 나중에 push, 스택에서 나중에 처리되어 R로 감)
            int right_child = 2 * current + 1;
            if (is_node_valid(right_child)) push(right_child);
        }
    }

    // 2. 출력 스택의 내용을 역순으로 출력 (L -> R -> Root 순서)
    while (output_top > -1) {
        printf("%c ", tree_array[output_stack[output_top--]]);
    }
}

void iterative_inorder_traversal() {
    printf("\nin-order: ");
    if (!is_node_valid(1)) return;
    top = -1;
    int current = 1;
    while (current != 0 || !is_empty()) {
        while (is_node_valid(current)) {
            push(current);
            current = 2 * current;
        }
        if (!is_empty()) {
            current = pop();
            printf("%c ", tree_array[current]);
            current = 2 * current + 1;
        }
    }
    printf("\n");
}

void iterative_postorder_traversal() {
    printf("\npost-order: ");
    if (!is_node_valid(1)) return;
    top = -1; output_top = -1;
    push(1);
    while (!is_empty()) {
        int current = pop();
        if (is_node_valid(current)) {
            push_output(current);
            int left_child = 2 * current;
            if (is_node_valid(left_child)) push(left_child);
            int right_child = 2 * current + 1;
            if (is_node_valid(right_child)) push(right_child);
        }
    }
    while (output_top > -1) {
        printf("%c ", tree_array[output_stack[output_top--]]);
    }
    printf("\n");
}

// -----------------------------------------------------------
int main() {
    // 배열로 변환할 이진 트리를 저장할 변수
    char input_buffer[INPUT_BUFFER_SIZE];
    char* current_pos;

    // 입력받은 것이 없다면 비정상적 종료
    if (fgets(input_buffer, INPUT_BUFFER_SIZE, stdin) == NULL) return 1;
    // 문자열 끝의 개행 문자를 제거해 괄호 > 배열 형태 변환에 오류가 없도록
    input_buffer[strcspn(input_buffer, "\n")] = 0;

    // 배열 초기화 및 파싱 시작
    memset(tree_array, '\0', sizeof(tree_array));
    current_pos = input_buffer;

    //printf("\n입력된 트리: %s\n", input_buffer);

    if (parse_and_insert(&current_pos, 1)) {
        //printf("파싱 성공. 순회를 시작합니다.\n");

        iterative_preorder_traversal();
        iterative_inorder_traversal();
        iterative_postorder_traversal();

    }
    else {
        printf("파싱 실패 또는 입력이 비어있거나 올바르지 않은 형식입니다.\n");
    }

    return 0;
}