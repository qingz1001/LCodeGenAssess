#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int a[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    while (q--) {
        int v;
        scanf("%d", &v);
        int result = 0;

        for (int j = 0; j < n; j++) {
            int max_val = 0;
            for (int i = 0; i < n; i++) {
                if (a[i][j] > max_val) {
                    max_val = a[i][j];
                }
            }
            if (max_val >= v) {
                result++;
            }
        }

        printf("%d\n", result);
    }

    return 0;
}