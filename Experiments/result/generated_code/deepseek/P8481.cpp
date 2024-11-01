#include <stdio.h>
#include <stdlib.h>

int find(int *num, int x, int len) {
    int l = 0, r = len - 1, mid, cnt = 0, w;
    while (l < r) {
        cnt++;
        w = rand() % 2;
        mid = (l + r + w) / 2;
        if (num[mid] - w < x) l = mid + !w;
        else r = mid - w;
    }
    return cnt;
}

int main() {
    int n, q, i;
    scanf("%d", &n);
    int *num = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    scanf("%d", &q);
    for (i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        printf("%d\n", find(num, x, n));
    }
    free(num);
    return 0;
}