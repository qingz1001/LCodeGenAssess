#include <stdio.h>
#include <string.h>
#define MAXN 200005
#define lowbit(x) ((x) & (-x))

long long tree[MAXN], arr[MAXN];
int n;

void update(int x, long long val) {
    for(int i = x; i <= n; i += lowbit(i))
        tree[i] += val;
}

long long query(int x) {
    long long sum = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        sum += tree[i];
    return sum;
}

int main() {
    int f, op, l, r;
    long long k;
    
    scanf("%d %d", &n, &f);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
        update(i, arr[i]);
    }
    
    while(f--) {
        scanf("%d", &op);
        switch(op) {
            case 1:
                scanf("%d %d %lld", &l, &r, &k);
                update(l, k);
                update(r+1, -k);
                break;
            case 2:
                scanf("%lld", &k);
                update(1, k);
                break;
            case 3:
                scanf("%lld", &k);
                update(1, -k);
                break;
            case 4:
                scanf("%d %d", &l, &r);
                printf("%lld\n", query(r) - query(l-1));
                break;
            case 5:
                printf("%lld\n", query(1));
                break;
        }
    }
    
    return 0;
}