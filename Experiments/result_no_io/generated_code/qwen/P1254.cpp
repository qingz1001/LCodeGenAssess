#include <stdio.h>
#include <stdlib.h>

#define MAX_N 8

int n;
int sectors[MAX_N];
int result[MAX_N * MAX_N];

void dfs(int index, int sum, int count) {
    if (index == n) {
        if (count > 0 && result[count - 1] + 1 == sum) {
            for (int i = 0; i < count; i++) {
                printf("%d ", result[i]);
            }
            printf("\n");
        }
        return;
    }

    // Choose the current sector
    if (sum + sectors[index] <= n * (n + 1) / 2) {
        result[count] = sectors[index];
        dfs(index + 1, sum + sectors[index], count + 1);
    }

    // Choose adjacent sectors
    for (int j = index + 1; j < n; j++) {
        if (sum + sectors[j] <= n * (n + 1) / 2) {
            result[count] = sectors[j];
            dfs(j + 1, sum + sectors[j], count + 1);
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &sectors[i]);
    }

    int max_i = 0;
    for (int i = 0; i < n; i++) {
        if (sectors[i] > max_i) {
            max_i = sectors[i];
        }
    }

    printf("%d\n", max_i);

    dfs(0, 0, 0);

    return 0;
}