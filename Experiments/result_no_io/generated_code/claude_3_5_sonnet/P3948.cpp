#include <stdio.h>
#include <string.h>

#define MAXN 100005

int n, opt, mod, min, max;
int arr[MAXN];

void update(int l, int r, int x) {
    for (int i = l; i <= r; i++) {
        arr[i] += x;
    }
}

int query(int l, int r) {
    int count = 0;
    for (int i = l; i <= r; i++) {
        long long val = (long long)arr[i] * i % mod;
        if (val < 0) val += mod;
        if (min <= val && val <= max) {
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d %d %d", &n, &opt, &mod, &min, &max);
    
    for (int i = 0; i < opt; i++) {
        char op;
        int l, r, x;
        scanf(" %c", &op);
        if (op == 'A') {
            scanf("%d %d %d", &l, &r, &x);
            update(l, r, x);
        } else if (op == 'Q') {
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