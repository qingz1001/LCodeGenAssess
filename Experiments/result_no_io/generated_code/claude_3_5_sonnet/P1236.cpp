#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_LEN 20

int nums[4];
char ops[] = {'+', '-', '*', '/'};
char expr[MAX_EXPR_LEN];
int used[4];

int calculate(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0 && a % b == 0) ? a / b : -1;
    }
    return -1;
}

int dfs(int depth, int result) {
    if (depth == 3) {
        return result == 24;
    }
    
    for (int i = 0; i < 4; i++) {
        if (!used[i]) {
            for (int j = i + 1; j < 4; j++) {
                if (!used[j]) {
                    used[i] = used[j] = 1;
                    for (int k = 0; k < 4; k++) {
                        int new_result;
                        if (nums[i] >= nums[j]) {
                            new_result = calculate(nums[i], nums[j], ops[k]);
                        } else {
                            new_result = calculate(nums[j], nums[i], ops[k]);
                        }
                        if (new_result > 0) {
                            int old_i = nums[i], old_j = nums[j];
                            nums[i] = new_result;
                            if (dfs(depth + 1, new_result)) {
                                printf("%d %c %d = %d\n", 
                                    (old_i >= old_j ? old_i : old_j),
                                    ops[k],
                                    (old_i >= old_j ? old_j : old_i),
                                    new_result);
                                return 1;
                            }
                            nums[i] = old_i;
                        }
                    }
                    used[i] = used[j] = 0;
                }
            }
        }
    }
    return 0;
}

int main() {
    for (int i = 0; i < 4; i++) {
        scanf("%d", &nums[i]);
    }
    
    if (!dfs(0, 0)) {
        printf("No answer!\n");
    }
    
    return 0;
}