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
    return mid;
}

int main() {
    int n, q;
    scanf("%d", &n);
    int num[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        printf("%d\n", find(num, x, n));
    }
    return 0;
}