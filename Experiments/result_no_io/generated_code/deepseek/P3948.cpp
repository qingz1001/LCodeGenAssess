#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXQ 1005

int n, opt, mod, min, max;
int arr[MAXN];

void add_range(int L, int R, int X) {
    for (int i = L; i <= R; i++) {
        arr[i] += X;
    }
}

int query_range(int L, int R) {
    int count = 0;
    for (int i = L; i <= R; i++) {
        int val = (arr[i] * i) % mod;
        if (val < 0) val += mod; // Handle negative modulo
        if (val >= min && val <= max) {
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
            add_range(L, R, X);
        } else if (op == 'Q') {
            scanf("%d %d", &L, &R);
            printf("%d\n", query_range(L, R));
        }
    }

    int Final;
    scanf("%d", &Final);
    for (int i = 0; i < Final; i++) {
        int L, R;
        scanf("%d %d", &L, &R);
        printf("%d\n", query_range(L, R));
    }

    return 0;
}