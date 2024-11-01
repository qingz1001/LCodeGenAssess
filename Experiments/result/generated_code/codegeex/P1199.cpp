#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int **compatibility = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        compatibility[i] = (int *)malloc((n - i) * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &compatibility[i][j]);
            compatibility[j][i] = compatibility[i][j];
        }
    }

    int maxCompatibility = 0;

    // 找出每个武将的最大和次大默契值
    for (int i = 0; i < n; i++) {
        int max1 = 0, max2 = 0;
        for (int j = 0; j < n; j++) {
            if (compatibility[i][j] > max1) {
                max2 = max1;
                max1 = compatibility[i][j];
            } else if (compatibility[i][j] > max2) {
                max2 = compatibility[i][j];
            }
        }
        if (max2 > maxCompatibility) {
            maxCompatibility = max2;
        }
    }

    printf("1\n%d\n", maxCompatibility);

    for (int i = 0; i < n; i++) {
        free(compatibility[i]);
    }
    free(compatibility);

    return 0;
}