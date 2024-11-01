#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500

int main() {
    int n;
    scanf("%d", &n);

    int默契值[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &默契值[i][j]);
            // 对称矩阵，填上另一半
           默契值[j][i] =默契值[i][j];
        }
    }

    int max默契值 = 0;
    for (int i = 0; i < n; i++) {
        int max1 = 0, max2 = 0;
        for (int j = 0; j < n; j++) {
            if (默契值[i][j] > max1) {
                max2 = max1;
                max1 =默契值[i][j];
            } else if (默契值[i][j] > max2) {
                max2 =默契值[i][j];
            }
        }
        if (max2 > max默契值) {
            max默契值 = max2;
        }
    }

    printf("1\n%d\n", max默契值);

    return 0;
}