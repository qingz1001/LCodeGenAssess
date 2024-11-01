#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int arr[MAXN];

void reverse(int L, int R) {
    for (int i = L; i <= R; i++) {
        arr[i] = 1 - arr[i];
    }
}

int query(int i) {
    return arr[i];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    while (m--) {
        int t, L, R, i;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &L, &R);
            reverse(L - 1, R - 1);
        } else if (t == 2) {
            scanf("%d", &i);
            printf("%d\n", query(i - 1));
        }
    }
    return 0;
}