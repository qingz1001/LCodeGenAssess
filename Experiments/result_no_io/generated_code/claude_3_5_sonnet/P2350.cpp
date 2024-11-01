#include <stdio.h>
#include <string.h>

#define MAX_M 2000
#define MOD 1000000007

typedef long long ll;

int test, m;
ll p[MAX_M], q[MAX_M];

ll power(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int solve() {
    int x = 0;
    while (1) {
        int is_one = 1;
        for (int i = 0; i < m; i++) {
            if (q[i] > 1) {
                is_one = 0;
                q[i]--;
            } else if (q[i] == 1) {
                q[i] = p[i] - 1;
                for (int j = 0; j < i; j++) {
                    q[j] = power(p[j], q[j], MOD);
                }
            }
        }
        x++;
        if (is_one) break;
    }
    return x;
}

int main() {
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%lld %lld", &p[i], &q[i]);
        }
        printf("%d\n", solve());
    }
    return 0;
}