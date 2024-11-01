#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define mod 998244353
#define maxn 128
#define maxm 20010

int n, m, N, K, cnt, ans;
int A[maxn][maxn], B[maxn][maxn], C[maxn][maxn], D[maxn][maxn];
int F[maxn][maxn], G[maxn], H[maxm], Q[maxm];

void mul(int a[maxn][maxn], int b[maxn][maxn], int c[maxn][maxn]) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0;
            for (k = 0; k < N; k++) {
                c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j] % mod) % mod;
            }
        }
    }
}

void mulself(int a[maxn][maxn], int b[maxn][maxn]) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            b[i][j] = 0;
            for (k = 0; k < N; k++) {
                b[i][j] = (b[i][j] + 1ll * a[i][k] * a[k][j] % mod) % mod;
            }
        }
    }
}

void init() {
    int i, j, k;
    N = 1;
    while (N < n) N <<= 1;
    K = N >> 1;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i < n && j < n) {
                B[i][j] = A[i][j];
            } else {
                B[i][j] = 0;
            }
        }
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < K; j++) {
            C[i][j] = B[i][j];
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            D[i][j] = 0;
        }
    }
    for (i = 0; i < N; i++) {
        D[i][i] = 1;
    }
    cnt = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (B[i][j]) {
                F[i][cnt++] = B[i][j];
            }
        }
    }
    for (i = 0; i < cnt; i++) {
        G[i] = F[i][0];
        for (j = 1; j < K; j++) {
            G[i] &= F[i][j];
        }
    }
    memset(H, 0, sizeof(H));
    for (i = 0; i < cnt; i++) {
        for (j = 0; j < K; j++) {
            if (G[i] & (1 << j)) {
                H[j]++;
            }
        }
    }
    for (i = 0; i < m; i++) {
        Q[i] = 0;
        for (j = 0; j < K; j++) {
            if (i & (1 << j)) {
                Q[i] += H[j];
            }
        }
    }
}

int main() {
    int i, j, k;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    init();
    for (i = 0; i < m; i++) {
        ans ^= Q[i];
    }
    printf("%d\n", ans);
    return 0;
}