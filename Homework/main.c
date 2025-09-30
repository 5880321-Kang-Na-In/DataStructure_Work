#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- ��� �� ���� �迭 ---
#define MAX_SIZE 2048
#define INPUT_BUFFER_SIZE 2048
char tree_array[MAX_SIZE] = { '\0', }; // Ʈ���� ������ �迭

// --- ���� ���� �Լ� �� ���� ---
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

// --- �Ľ� �Լ� (������ ����) ---
int parse_and_insert(char** str_ptr, int index) {
    char* str = *str_ptr;

    if (index >= MAX_SIZE) return 0;

    // 1. ���� �ǳʶٱ�
    while (*str == ' ' || *str == '\n') str++;

    // 2. '(' Ȯ�� �� ����ִ� �Է� ó��
    if (*str != '(') { *str_ptr = str; return 0; }
    str++; // '(' �ǳʶٱ�

    // 3. ��� �� Ȯ�� �� ���� �Ǵ� NULL ��� ó��
    while (*str == ' ' || *str == '\n') str++;
    if (*str == ')') {
        str++; // ')' �ǳʶٱ� -> NULL ���
        *str_ptr = str;
        return 0;
    }

    // ��� �� ���� (index ��ġ��)
    if (*str != '\0') {
        tree_array[index] = *str;
        str++; // ��� �� �ǳʶٱ�
    }
    else {
        // ���ڿ� ���� ���� (����)
        *str_ptr = str;
        return 0;
    }

    // 4. ���� ����Ʈ�� �Ľ�
    parse_and_insert(&str, 2 * index);

    // 5. ������ ����Ʈ�� �Ľ�
    parse_and_insert(&str, 2 * index + 1);

    // 6. ')' �ݴ� ��ȣ Ȯ�� �� �ǳʶٱ�
    while (*str == ' ' || *str == '\n') str++;
    if (*str == ')') {
        str++; // ')' �ǳʶٱ�
    }

    *str_ptr = str;
    return 1;
}

// --- ��ȸ �Լ��� ---
void iterative_preorder_traversal() {
    printf("\npre-order: ");
    if (!is_node_valid(1)) return;

    // �ݵ�� ���� �ʱ�ȭ: ���� ��ȸ���� ������� �� �����Ƿ�
    top = -1; output_top = -1;
    push(1);

    // 1. ���� ���ÿ��� R -> L -> Root ������ pop�ϸ鼭 ����� ��� ���ÿ� ����
    while (!is_empty()) {
        int current = pop();

        // ��ȿ�� ������� �ٽ� �ѹ� Ȯ�� (tree_array�� ���� �ִ���)
        if (is_node_valid(current)) {
            push_output(current); // ��� ���ÿ� ���� (Root)

            // R (������ �ڽ� ���� push, ���ÿ��� ���� ó���Ǿ� L�� ��)
            int left_child = 2 * current;
            if (is_node_valid(left_child)) push(left_child);

            // L (���� �ڽ� ���߿� push, ���ÿ��� ���߿� ó���Ǿ� R�� ��)
            int right_child = 2 * current + 1;
            if (is_node_valid(right_child)) push(right_child);
        }
    }

    // 2. ��� ������ ������ �������� ��� (L -> R -> Root ����)
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
    // �迭�� ��ȯ�� ���� Ʈ���� ������ ����
    char input_buffer[INPUT_BUFFER_SIZE];
    char* current_pos;

    // �Է¹��� ���� ���ٸ� �������� ����
    if (fgets(input_buffer, INPUT_BUFFER_SIZE, stdin) == NULL) return 1;
    // ���ڿ� ���� ���� ���ڸ� ������ ��ȣ > �迭 ���� ��ȯ�� ������ ������
    input_buffer[strcspn(input_buffer, "\n")] = 0;

    // �迭 �ʱ�ȭ �� �Ľ� ����
    memset(tree_array, '\0', sizeof(tree_array));
    current_pos = input_buffer;

    //printf("\n�Էµ� Ʈ��: %s\n", input_buffer);

    if (parse_and_insert(&current_pos, 1)) {
        //printf("�Ľ� ����. ��ȸ�� �����մϴ�.\n");

        iterative_preorder_traversal();
        iterative_inorder_traversal();
        iterative_postorder_traversal();

    }
    else {
        printf("�Ľ� ���� �Ǵ� �Է��� ����ְų� �ùٸ��� ���� �����Դϴ�.\n");
    }

    return 0;
}