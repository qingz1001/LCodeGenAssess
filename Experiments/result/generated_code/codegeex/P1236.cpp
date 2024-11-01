#include <stdio.h>
#include <stdlib.h>

int numbers[4];
char ops[] = {'+', '-', '*', '/'};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_step(int a, int b, char op, int result) {
    if (a > b) {
        printf("%d%c%d=%d\n", a, op, b, result);
    } else {
        printf("%d%c%d=%d\n", b, op, a, result);
    }
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

void solve(int *nums, int index, int result) {
    if (index == 3) {
        if (result == 24) {
            printf("%d=%d\n", result, 24);
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        int a = nums[index];
        int b = nums[index + 1];
        for (int j = 0; j < 4; j++) {
            int temp_result = calculate(a, b, ops[j]);
            if (temp_result > 0 && (ops[j] == '+' || ops[j] == '*' || (ops[j] == '-' && temp_result > b) || (ops[j] == '/' && b != 0 && a % b == 0))) {
                print_step(a, b, ops[j], temp_result);
                int new_nums[4] = {temp_result};
                for (int k = 0; k < index; k++) {
                    new_nums[k] = nums[k];
                }
                for (int k = index + 2; k < 4; k++) {
                    new_nums[k - 1] = nums[k];
                }
                solve(new_nums, index - 1, result);
            }
        }
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        scanf("%d", &numbers[i]);
    }

    solve(numbers, 3, 0);

    if (result != 24) {
        printf("No answer!\n");
    }

    return 0;
}