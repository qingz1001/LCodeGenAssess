#include <stdio.h>
#define MAXN 100005

int arr[MAXN];

void reverse(int L, int R) {
    for (int i = L; i <= R; i++) {
        arr[i] = 1 - arr[i];
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        arr[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int t, L, R;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &L, &R);
            reverse(L, R);
        } else if (t == 2) {
            scanf("%d", &L);
            printf("%d\n", arr[L]);
        }
    }
    return 0;
}