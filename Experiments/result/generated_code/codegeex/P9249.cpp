#include <stdio.h>
#include <string.h>
#include <algorithm>
#define N 128
#define M 20001
#define mod 998244353
using namespace std;

int n, m, N;
int A[N][N], tr[M], tr0[M], tr1[M], res[M], ans[M], f[M][N];

int main() {
    scanf("%d%d", &n, &m);
    N = 1 << n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    tr[0] = 1;
    for (int i = 1; i <= m; i++) tr[i] = 1ll * tr[i-1] * i % mod;

    tr0[0] = 1;
    for (int i = 1; i <= m; i++) tr0[i] = 1ll * tr0[i-1] * (i-1) % mod;

    tr1[0] = 1;
    for (int i = 1; i <= m; i++) tr1[i] = 1ll * tr1[i-1] * i % mod;

    for (int S = 0; S < N; S++) {
        memset(f, 0, sizeof(f));
        f[0][S] = 1;
        for (int k = 0; k < n; k++) {
            for (int T = 0; T < N; T++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (T & (1 << i)) {
                            f[A[k][j]][T ^ (1 << j)] = (f[A[k][j]][T ^ (1 << j)] + 1ll * f[A[k][j]][T] * tr[A[k][i]]) % mod;
                        }
                    }
                }
            }
        }
        for (int x = 1; x <= m; x++) {
            for (int T = 0; T < N; T++) {
                if (T & S) {
                    res[x] = (res[x] + f[x][T]) % mod;
                }
            }
        }
    }

    for (int x = 1; x <= m; x++) {
        int sum = 0;
        for (int T = 0; T < N; T++) {
            if (T & S) {
                sum = (sum + 1ll * f[x][T] * tr1[(x-1)&T] % mod * tr0[x - (x-1)&T]) % mod;
            }
        }
        ans[x] = sum;
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            ans ^= 1ll * res[i] * tr1[j] % mod;
        }
    }

    printf("%d\n", ans);
    return 0;
}