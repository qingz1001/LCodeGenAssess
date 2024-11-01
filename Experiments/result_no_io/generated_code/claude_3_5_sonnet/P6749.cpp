#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXM 30005

long long a[MAXN], tree[MAXN];
int n, m;

long long lowbit(long long x) {
    return x & (-x);
}

void update(int x, int val) {
    while (x <= n) {
        tree[x] += val;
        x += lowbit(x);
    }
}

long long query(int x) {
    long long sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

long long count_inversions() {
    long long inversions = 0;
    for (int i = 1; i <= n; i++) {
        inversions += i - 1 - query(a[i]);
        update(a[i], 1);
    }
    for (int i = 1; i <= n; i++) {
        update(a[i], -1);
    }
    return inversions;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            for (int j = l; j <= r; j++) {
                a[j] = x + j - l;
            }
        } else if (op == 2) {
            printf("%lld\n", count_inversions());
        }
    }
    
    return 0;
}