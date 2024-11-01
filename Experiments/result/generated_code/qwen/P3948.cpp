#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MOD 2147483647

int n, opt, mod, min, max;
int a[MAXN];

void update(int L, int R, int X) {
    for (int i = L; i <= R; i++) {
        a[i] = (a[i] + X) % MOD;
    }
}

int query(int L, int R) {
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (min <= ((long long)a[i] * i) % MOD && ((long long)a[i] * i) % MOD <= max) {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d %d %d", &n, &opt, &mod, &min, &max);
    for (int i = 0; i < opt; i++) {
        char op;
        int L, R, X;
        scanf(" %c", &op);
        if (op == 'A') {
            scanf("%d %d %d", &L, &R, &X);
            update(L - 1, R - 1, X);
        } else if (op == 'Q') {
            scanf("%d %d", &L, &R);
            printf("%d\n", query(L - 1, R - 1));
        }
    }
    int final;
    scanf("%d", &final);
    for (int i = 0; i < final; i++) {
        int L, R;
        scanf("%d %d", &L, &R);
        printf("%d\n", query(L - 1, R - 1));
    }
    return 0;
}