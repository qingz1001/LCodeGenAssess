#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 1000000000

typedef struct {
    int size;
    int value;
} File;

int n, p, S;
File files[MAXN];

int compare(const void *a, const void *b) {
    return ((File *)a)->size - ((File *)b)->size;
}

int canAchieve(int L) {
    int dp[MAXN] = {0};
    int total_size = 0;

    for (int i = 0; i < n; i++) {
        if (files[i].size <= L) {
            for (int j = S; j >= files[i].size; j--) {
                if (dp[j - files[i].size] + files[i].value > dp[j]) {
                    dp[j] = dp[j - files[i].size] + files[i].value;
                }
            }
        }
    }

    for (int i = 0; i <= S; i++) {
        if (dp[i] >= p) {
            return 1;
        }
    }

    return 0;
}

int main() {
    scanf("%d %d %d", &n, &p, &S);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &files[i].size, &files[i].value);
    }

    qsort(files, n, sizeof(File), compare);

    int left = 1, right = INF;
    int result = -1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (canAchieve(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (result == -1) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}