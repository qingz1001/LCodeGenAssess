#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef long long ll;

ll a[MAXN];

int main() {
    int n, f;
    scanf("%d %d", &n, &f);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    while (f--) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            int l, r;
            ll k;
            scanf("%d %d %lld", &l, &r, &k);
            for (int i = l; i <= r; i++) {
                a[i] += k;
            }
        } else if (op == 2) {
            ll k;
            scanf("%lld", &k);
            a[1] += k;
        } else if (op == 3) {
            ll k;
            scanf("%lld", &k);
            a[1] -= k;
        } else if (op == 4) {
            int l, r;
            scanf("%d %d", &l, &r);
            ll sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            printf("%lld\n", sum);
        } else if (op == 5) {
            printf("%lld\n", a[1]);
        }
    }
    
    return 0;
}