#include <stdio.h>
#include <stdlib.h>

int find(int *num, int x, int len) {
    int l = 0, r = len - 1, mid, cnt = 0;
    while (l < r) {
        cnt++;
        int w = rand() % 2;
        mid = (l + r + w) / 2;
        if (num[mid] < x) l = mid + 1;
        else r = mid;
    }
    return cnt;
}

int main() {
    int n;
    scanf("%d", &n);
    int num[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        printf("%d\n", find(num, x, n));
    }
    return 0;
}