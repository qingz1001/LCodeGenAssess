#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_SUM 15000001

int n, k;
int nums[MAX_N];
bool is_prime[MAX_SUM];
int count = 0;

void sieve() {
    for (int i = 2; i < MAX_SUM; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i * i < MAX_SUM; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAX_SUM; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void dfs(int start, int depth, int sum) {
    if (depth == k) {
        if (is_prime[sum]) {
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

    sieve();
    dfs(0, 0, 0);

    printf("%d\n", count);
    return 0;
}