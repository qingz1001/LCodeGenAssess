#include <stdio.h>
#include <string.h>

#define MOD 1000000007

typedef long long ll;

ll pow3[1010];

int main() {
    int n, m, c, q;
    scanf("%d%d%d%d", &n, &m, &c, &q);
    pow3[0] = 1;
    for (int i = 1; i <= n * m; i++) {
        pow3[i] = (pow3[i - 1] * 3) % MOD;
    }
    while (q--) {
        char a[10], b[10];
        scanf("%s%s", a, b);
        int cnt = 0;
        for (int i = 0; i < c; i++) {
            if (a[i] == 'B' && b[i] == 'B') cnt++;
        }
        ll ans = pow3[n * m - cnt];
        for (int i = 0; i < c; i++) {
            if (a[i] == 'B' && b[i] == 'X') {
                ans = (ans * 2) % MOD;
            }
        }
        for (int i = 0; i < c; i++) {
            if (a[i] == 'X' && b[i] == 'B') {
                ans = (ans * 2) % MOD;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}