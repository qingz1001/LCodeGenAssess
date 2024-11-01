#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30005
#define lowbit(x) ((x) & (-x))

long long BIT[MAXN];
int a[MAXN], n, m;

void update(int x, int val) {
    for(; x <= n; x += lowbit(x))
        BIT[x] += val;
}

long long query(int x) {
    long long sum = 0;
    for(; x > 0; x -= lowbit(x))
        sum += BIT[x];
    return sum;
}

long long count_inversions() {
    long long inv_count = 0;
    memset(BIT, 0, sizeof(BIT));
    
    for(int i = n; i > 0; i--) {
        inv_count += query(a[i] - 1);
        update(a[i], 1);
    }
    
    return inv_count;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    
    for(int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        
        if(op == 1) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            for(int j = l; j <= r; j++)
                a[j] = x + (j - l);
        } else {
            printf("%lld\n", count_inversions());
        }
    }
    
    return 0;
}