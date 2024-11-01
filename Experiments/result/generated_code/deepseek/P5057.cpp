#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int arr[MAXN];
int lazy[MAXN];

void update(int L, int R, int n) {
    for (int i = L; i <= R; i++) {
        lazy[i] ^= 1;
    }
}

int query(int i) {
    return arr[i] ^ lazy[i];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int t, L, R;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &L, &R);
            update(L, R, n);
        } else if (t == 2) {
            scanf("%d", &L);
            printf("%d\n", query(L));
        }
    }

    return 0;
}