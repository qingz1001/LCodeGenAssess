#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);

    ll *a = (ll *)malloc(n * sizeof(ll));
    ll *b = (ll *)malloc(m * sizeof(ll));

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    ll **A = (ll **)malloc(n * sizeof(ll *));
    for (int i = 0; i < n; i++) {
        A[i] = (ll *)malloc(m * sizeof(ll));
        for (int j = 0; j < m; j++) {
            A[i][j] = a[i] * b[j];
        }
    }

    ll **B = (ll **)malloc((n + 1) * sizeof(ll *));
    for (int i = 0; i <= n; i++) {
        B[i] = (ll *)malloc(t * sizeof(ll));
        for (int j = 0; j < t; j++) {
            B[i][j] = (i % 2 == 0) ? j % m : (j + 1) % m;
        }
    }

    ll fB = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t; j++) {
            for (int k = min(B[i][j], B[i + 1][j]); k <= max(B[i][j], B[i + 1][j]); k++) {
                fB = (fB + A[i][k]) % MOD;
            }
        }
    }

    printf("%lld\n", fB);

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i <= n; i++) {
        free(B[i]);
    }
    free(B);

    free(a);
    free(b);

    return 0;
}