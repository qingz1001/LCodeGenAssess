#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define BLOCK_SIZE 450

typedef long long ll;

int n, q;
ll a[MAXN];
int block[MAXN], block_cnt;
ll block_add[MAXN];

void init() {
    block_cnt = (n - 1) / BLOCK_SIZE + 1;
    for (int i = 1; i <= n; i++) {
        block[i] = (i - 1) / BLOCK_SIZE + 1;
    }
}

void update(int l, int r, ll d) {
    int bl = block[l], br = block[r];
    if (bl == br) {
        for (int i = l; i <= r; i++) {
            a[i] += d;
        }
    } else {
        for (int i = l; i <= bl * BLOCK_SIZE; i++) {
            a[i] += d;
        }
        for (int i = bl + 1; i < br; i++) {
            block_add[i] += d;
        }
        for (int i = (br - 1) * BLOCK_SIZE + 1; i <= r; i++) {
            a[i] += d;
        }
    }
}

int query(int l, int r) {
    int res = r;
    ll min_val = a[r] + block_add[block[r]];
    for (int i = r - 1; i >= l; i--) {
        ll cur = a[i] + block_add[block[i]];
        if (cur < min_val || (cur == min_val && i < res)) {
            min_val = cur;
            res = i;
        }
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    init();
    
    while (q--) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            ll d;
            scanf("%lld", &d);
            update(l, r, d);
        } else {
            printf("%d\n", query(l, r));
        }
    }
    
    return 0;
}