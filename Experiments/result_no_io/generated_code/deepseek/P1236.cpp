#include <stdio.h>
#include <stdbool.h>

bool solve24(int nums[], char ops[], int target);
bool solve(int a, int b, int c, int d, char ops[]);
bool valid(int a, int b, char op);

int main() {
    int nums[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d", &nums[i]);
    }

    char ops[3];
    if (solve(nums[0], nums[1], nums[2], nums[3], ops)) {
        printf("%d %c %d = %d\n", nums[0], ops[0], nums[1], nums[0] + nums[1]);
        printf("%d %c %d = %d\n", nums[0] + nums[1], ops[1], nums[2], nums[0] + nums[1] + nums[2]);
        printf("%d %c %d = 24\n", nums[0] + nums[1] + nums[2], ops[2], nums[3], 24);
    } else {
        printf("No answer!\n");
    }

    return 0;
}

bool solve(int a, int b, int c, int d, char ops[]) {
    int nums[4] = {a, b, c, d};
    char all_ops[] = {'+', '-', '*', '/'};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                ops[0] = all_ops[i];
                ops[1] = all_ops[j];
                ops[2] = all_ops[k];

                if (solve24(nums, ops, 24)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool solve24(int nums[], char ops[], int target) {
    int a = nums[0], b = nums[1], c = nums[2], d = nums[3];
    char op1 = ops[0], op2 = ops[1], op3 = ops[2];

    // Check all possible combinations of operations
    if (valid(a, b, op1) && valid(c, d, op2)) {
        int result1 = (op1 == '+' ? a + b : op1 == '-' ? a - b : op1 == '*' ? a * b : a / b);
        int result2 = (op2 == '+' ? c + d : op2 == '-' ? c - d : op2 == '*' ? c * d : c / d);
        if (valid(result1, result2, op3) && (op3 == '+' ? result1 + result2 : op3 == '-' ? result1 - result2 : op3 == '*' ? result1 * result2 : result1 / result2) == target) {
            return true;
        }
    }

    if (valid(a, c, op1) && valid(b, d, op2)) {
        int result1 = (op1 == '+' ? a + c : op1 == '-' ? a - c : op1 == '*' ? a * c : a / c);
        int result2 = (op2 == '+' ? b + d : op2 == '-' ? b - d : op2 == '*' ? b * d : b / d);
        if (valid(result1, result2, op3) && (op3 == '+' ? result1 + result2 : op3 == '-' ? result1 - result2 : op3 == '*' ? result1 * result2 : result1 / result2) == target) {
            return true;
        }
    }

    if (valid(a, d, op1) && valid(b, c, op2)) {
        int result1 = (op1 == '+' ? a + d : op1 == '-' ? a - d : op1 == '*' ? a * d : a / d);
        int result2 = (op2 == '+' ? b + c : op2 == '-' ? b - c : op2 == '*' ? b * c : b / c);
        if (valid(result1, result2, op3) && (op3 == '+' ? result1 + result2 : op3 == '-' ? result1 - result2 : op3 == '*' ? result1 * result2 : result1 / result2) == target) {
            return true;
        }
    }

    return false;
}

bool valid(int a, int b, char op) {
    if (op == '/' && b == 0) return false;
    if (op == '/' && a % b != 0) return false;
    return true;
}