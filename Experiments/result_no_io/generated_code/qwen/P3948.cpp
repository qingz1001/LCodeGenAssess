#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MOD 2147483647

int n, opt, mod, min, max;
int a[MAXN];

void update(int L, int R, int X) {
    for (int i = L; i <= R; i++) {
        a[i] = (a[i] + X) % mod;
    }
}

int query(int L, int R) {
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (min <= (a[i] * i) % mod && (a[i] * i) % mod <= max) {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d %d %d", &n, &opt, &mod, &min, &max);
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }

    for (int i = 0; i < opt; i++) {
        int type, l, r, x;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &l, &r, &x);
            update(l, r, x);
        } else if (type == 2) {
            scanf("%d %d", &l, &r);
            printf("%d\n", query(l, r));
        }
    }

    int final;
    scanf("%d", &final);
    for (int i = 0; i < final; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", query(l, r));
    }

    return 0;
}