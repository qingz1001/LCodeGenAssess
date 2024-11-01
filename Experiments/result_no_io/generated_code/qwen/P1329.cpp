#include <stdio.h>
#include <stdlib.h>

#define MOD 18446744073709551615ULL

void dfs(int n, int s, int *path, int index, unsigned long long *count, unsigned long long **result, int *result_count) {
    if (index == n) {
        (*count)++;
        if (*result_count < 100) {
            for (int i = 0; i < n; i++) {
                result[*result_count][i] = path[i];
            }
            (*result_count)++;
        }
        return;
    }

    if (index > 0 && abs(path[index - 1] - s) != 1) {
        return;
    }

    path[index] = s;
    dfs(n, s + 1, path, index + 1, count, result, result_count);
    dfs(n, s - 1, path, index + 1, count, result, result_count);
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    unsigned long long count = 0;
    unsigned long long *result = (unsigned long long *)malloc(100 * n * sizeof(unsigned long long));
    int result_count = 0;

    int *path = (int *)malloc(n * sizeof(int));
    dfs(n, s, path, 0, &count, &result, &result_count);

    printf("%llu\n", count % MOD);
    for (int i = 0; i < result_count; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lld ", result[i * n + j]);
        }
        printf("\n");
    }

    free(result);
    free(path);

    return 0;
}