#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500

int n;
int默契值[MAXN][MAXN];
int used[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &默契值[i][j]);
            默契值[j][i] = 默契值[i][j];
        }
    }

    int max_默契值 = 0;
    for (int i = 0; i < n; i++) {
        int max_local = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                max_local = max(max_local, 默契值[i][j]);
            }
        }
        max_默契值 = max(max_默契值, max_local);
    }

    printf("1\n%d\n", max_默契值);

    return 0;
}