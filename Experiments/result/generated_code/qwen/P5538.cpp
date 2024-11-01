#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 786433

typedef long long ll;

ll modpow(ll base, ll exp) {
    if (exp == 0) return 1;
    ll half = modpow(base, exp / 2);
    ll res = half * half % MOD;
    if (exp % 2 == 1) res = res * base % MOD;
    return res;
}

void ntt(int *a, int n, int inv) {
    for (int i = 1; i < n; i <<= 1) {
        int w = modpow(10, (MOD - 1) / (i << 1));
        if (inv) w = modpow(w, MOD - 2);
        for (int j = 0; j < n; j += i << 1) {
            int u = 1;
            for (int k = 0; k < i; k++) {
                int t = a[j + k + i] * u % MOD;
                a[j + k + i] = (a[j + k] - t + MOD) % MOD;
                a[j + k] = (a[j + k] + t) % MOD;
                u = u * w % MOD;
            }
        }
    }
    if (inv) {
        int n_inv = modpow(n, MOD - 2);
        for (int i = 0; i < n; i++) a[i] = a[i] * n_inv % MOD;
    }
}

void multiply(int *a, int *b, int *res, int n) {
    memset(res, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            res[i] = (res[i] + (ll)a[j] * b[i - j]) % MOD;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int edges[n - 1][2];
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &edges[i][0], &edges[i][1]);
    }

    // Build adjacency list
    int adj[n][n];
    memset(adj, 0, sizeof(int) * n * n);
    for (int i = 0; i < n - 1; i++) {
        adj[edges[i][0] - 1][edges[i][1] - 1] = 1;
        adj[edges[i][1] - 1][edges[i][0] - 1] = 1;
    }

    // DFS to calculate the number of paths and their weights
    int path_count[n];
    int path_weight[n];
    memset(path_count, 0, sizeof(int) * n);
    memset(path_weight, 0, sizeof(int) * n);

    void dfs(int node, int parent, int count, int weight) {
        path_count[node] = count;
        path_weight[node] = weight;
        for (int i = 0; i < n; i++) {
            if (adj[node][i] && i != parent) {
                dfs(i, node, count + 1, weight | a[i]);
            }
        }
    }

    dfs(0, -1, 0, 0);

    // Calculate the result using FFT
    int result = 0;
    int A[n], B[n], C[n];
    for (int i = 0; i < n; i++) {
        A[i] = path_count[i];
        B[i] = path_weight[i];
    }
    multiply(A, B, C, n);

    for (int i = 0; i < n; i++) {
        result = (result + C[i] * modpow(C[i], C[i])) % MOD;
    }

    printf("%d\n", result);

    return 0;
}