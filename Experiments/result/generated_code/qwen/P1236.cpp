#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMS 4
#define TARGET 24

typedef struct {
    int value;
    char op;
} Node;

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': if (b != 0) return a / b; else return -1;
        default: return -1;
    }
}

void print_result(Node *nodes, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d%c%d=%d\n", nodes[i].value, nodes[i].op, nodes[i + 1].value, calculate(nodes[i].value, nodes[i + 1].value, nodes[i].op));
    }
}

int solve(Node *nums, int count) {
    if (count == 1) {
        if (nums[0].value == TARGET) {
            print_result(nums, 0);
            return 1;
        } else {
            return 0;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (char op : "+-*/") {
            Node new_nums[MAX_NUMS];
            int new_count = 0;

            // Combine the current operation result with the remaining numbers
            for (int j = 0; j < count; j++) {
                if (j != i && j != i + 1) {
                    new_nums[new_count++] = nums[j];
                }
            }
            new_nums[new_count++] = (Node){calculate(nums[i].value, nums[i + 1].value, op), op};

            if (solve(new_nums, new_count)) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    int nums[MAX_NUMS];
    scanf("%d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3]);

    Node nodes[MAX_NUMS];
    for (int i = 0; i < MAX_NUMS; i++) {
        nodes[i] = (Node){nums[i], '\0'};
    }

    if (!solve(nodes, MAX_NUMS)) {
        printf("No answer!\n");
    }

    return 0;
}