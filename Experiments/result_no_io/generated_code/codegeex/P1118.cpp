#include <stdio.h>
#include <stdbool.h>

bool used[13];
int a[13];

bool check(int n, int sum) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += a[i] * (n - i);
    }
    return total == sum;
}

void dfs(int n, int sum, int pos) {
    if (pos == n) {
        if (check(n, sum)) {
            for (int i = 0; i < n; i++) {
                printf("%d ", a[i]);
            }
            printf("\n");
            exit(0);
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            a[pos] = i;
            used[i] = true;
            dfs(n, sum, pos + 1);
            used[i] = false;
        }
    }
}

int main() {
    int n, sum;
    scanf("%d %d", &n, &sum);
    dfs(n, sum, 0);
    return 0;
}