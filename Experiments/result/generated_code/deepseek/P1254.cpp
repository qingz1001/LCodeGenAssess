#include <stdio.h>
#include <stdbool.h>

#define MAX_N 8

int n;
int sectors[MAX_N];
bool used[MAX_N + 1];
int max_i = 0;

void print_solution() {
    for (int i = 0; i < n; i++) {
        printf("%d ", sectors[i]);
    }
    printf("\n");
}

bool can_form_sequence(int target) {
    bool dp[MAX_N * MAX_N + 1] = {false};
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = target; j >= sectors[i]; j--) {
            if (dp[j - sectors[i]]) {
                dp[j] = true;
            }
        }
    }

    for (int i = 1; i <= target; i++) {
        if (!dp[i]) return false;
    }
    return true;
}

void backtrack(int index, int current_sum) {
    if (index == n) {
        if (can_form_sequence(current_sum)) {
            if (current_sum > max_i) {
                max_i = current_sum;
                printf("%d\n", max_i);
                print_solution();
            } else if (current_sum == max_i) {
                print_solution();
            }
        }
        return;
    }

    for (int i = 1; i <= n * n; i++) {
        if (!used[i]) {
            used[i] = true;
            sectors[index] = i;
            backtrack(index + 1, current_sum + i);
            used[i] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    backtrack(0, 0);
    return 0;
}