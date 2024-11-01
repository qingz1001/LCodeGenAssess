#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

typedef long long ll;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int m, K;
        scanf("%d%d", &m, &K);
        
        if (K == 1) {
            printf("1\n");
            continue;
        }
        
        int n = 1;
        while (true) {
            ll g = gcd(n * m, K);
            if (g == 1) {
                printf("%d\n", n);
                break;
            }
            if (n > MAXN) {
                printf("-1\n");
                break;
            }
            n++;
        }
    }
    return 0;
}