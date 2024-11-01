#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

int n, m;
int a[MAXN], b[MAXN], c[MAXN];
int type[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &type[i]);
        if (type[i] == 1) {
            scanf("%d %d %d", &a[i], &b[i], &c[i]);
        } else if (type[i] == 2) {
            scanf("%d %d %d", &a[i], &b[i], &c[i]);
        } else {
            scanf("%d %d", &a[i], &b[i]);
        }
    }

    int *x = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        x[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        if (type[i] == 1) {
            if (x[a[i] - 1] + c[i] > x[b[i] - 1]) {
                printf("No\n");
                return 0;
            }
            x[a[i] - 1] += c[i];
        } else if (type[i] == 2) {
            if (x[a[i] - 1] < x[b[i] - 1] - c[i]) {
                printf("No\n");
                return 0;
            }
            x[a[i] - 1] = x[b[i] - 1] - c[i];
        } else {
            if (x[a[i] - 1] != x[b[i] - 1]) {
                printf("No\n");
                return 0;
            }
            x[a[i] - 1] = x[b[i] - 1];
        }
    }

    printf("Yes\n");

    free(x);
    return 0;
}