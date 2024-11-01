#include <stdio.h>
#include <stdbool.h>

#define MAXN 20

int n, k;
int nums[MAXN];
int count = 0;

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void dfs(int start, int depth, int sum) {
    if (depth == k) {
        if (is_prime(sum)) {
            count++;
        }
        return;
    }
    for (int i = start; i < n; i++) {
        dfs(i + 1, depth + 1, sum + nums[i]);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    dfs(0, 0, 0);
    printf("%d\n", count);
    return 0;
}