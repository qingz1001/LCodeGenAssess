#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *arr = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        arr[i] = 0;
    }

    while (m--) {
        int q, l, r;
        scanf("%d %d %d", &q, &l, &r);
        if (q == 1) {
            for (int i = l; i <= r; i++) {
                if (arr[i] == 0) {
                    arr[i] = 1;
                }
            }
        } else if (q == 2) {
            int count = 0;
            for (int i = l; i <= r; i++) {
                if (arr[i] == 1) {
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }

    free(arr);
    return 0;
}