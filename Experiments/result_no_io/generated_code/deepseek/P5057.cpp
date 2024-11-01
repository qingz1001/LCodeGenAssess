#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int arr[MAXN];
int lazy[MAXN];

void update(int L, int R) {
    for (int i = L; i <= R; i++) {
        arr[i] ^= 1;
    }
}

int query(int i) {
    return arr[i];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int t, L, R, idx;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &L, &R);
            update(L, R);
        } else if (t == 2) {
            scanf("%d", &idx);
            printf("%d\n", query(idx));
        }
    }
    return 0;
}