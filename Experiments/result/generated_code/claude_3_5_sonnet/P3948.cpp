#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

long long arr[MAXN];
int n, opt, mod, min, max;

void update(int l, int r, long long x) {
    for (int i = l; i <= r; i++) {
        arr[i] += x;
    }
}

int query(int l, int r) {
    int count = 0;
    for (int i = l; i <= r; i++) {
        long long val = (arr[i] * i) % mod;
        if (val < 0) val += mod;
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
        scanf(" %c", &op);
        if (op == 'A') {
            int l, r;
            long long x;
            scanf("%d %d %lld", &l, &r, &x);
            update(l, r, x);
        } else if (op == 'Q') {
            int l, r;
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