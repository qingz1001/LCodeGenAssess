#include <stdio.h>
#include <stdlib.h>

int n, p, S;
int dp[1001];

struct File {
    int size;
    int value;
} files[1001];

int cmp(const void *a, const void *b) {
    struct File *fileA = (struct File *)a;
    struct File *fileB = (struct File *)b;
    return fileA->size - fileB->size;
}

int main() {
    scanf("%d %d %d", &n, &p, &S);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &files[i].size, &files[i].value);
    }

    // Sort files by size
    qsort(files + 1, n, sizeof(struct File), cmp);

    // Initialize dp array
    for (int i = 1; i <= S; i++) {
        dp[i] = 0;
    }

    // Knapsack problem using dynamic programming
    for (int i = 1; i <= n; i++) {
        for (int j = S; j >= files[i].size; j--) {
            if (dp[j] < dp[j - files[i].size] + files[i].value) {
                dp[j] = dp[j - files[i].size] + files[i].value;
            }
        }
    }

    // Find the minimum interface size
    int minInterfaceSize = 0;
    for (int i = 1; i <= S; i++) {
        if (dp[i] >= p) {
            minInterfaceSize = i;
            break;
        }
    }

    if (minInterfaceSize == 0) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", minInterfaceSize);
    }

    return 0;
}