#include <stdio.h>
#include <stdlib.h>

#define MAXN 50
#define MAXM 100

void print_stereogram(int m, int n, int height[MAXN][MAXN]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (height[i][j] == 0) {
                printf("........");
            } else {
                for (int k = 0; k < height[i][j]; k++) {
                    if (k % 2 == 0) {
                        printf("..+---+");
                    } else {
                        printf("+---+  ");
                    }
                }
            }
        }
        printf("\n");
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int height[MAXN][MAXN];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    print_stereogram(m, n, height);
    return 0;
}