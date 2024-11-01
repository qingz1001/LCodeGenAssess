#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXM 1005
#define INF 0x3f3f3f3f

typedef long long ll;

int n, m, q;
ll x0, a, b, c, d;
int T[MAXN * MAXM];
int A[MAXN][MAXM];
int dp[MAXN][MAXM];
int path[MAXN + MAXM];

ll random_generate() {
    x0 = (a * x0 * x0 + b * x0 + c) % d;
    return x0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void init_permutation() {
    int i, j;
    for (i = 1; i <= n * m; i++) {
        T[i] = i;
    }
    for (i = 1; i <= n * m; i++) {
        j = random_generate() % i + 1;
        swap(&T[i], &T[j]);
    }
}

void extra_swap() {
    int i, u, v;
    for (i = 0; i < q; i++) {
        scanf("%d %d", &u, &v);
        swap(&T[u], &T[v]);
    }
}

void fill_board() {
    int i, j, k = 1;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            A[i][j] = T[k++];
        }
    }
}

void solve() {
    int i, j, k;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    dp[1][1] = A[1][1];
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (i > 1) {
                dp[i][j] = dp[i-1][j] < dp[i][j] ? dp[i-1][j] : dp[i][j];
            }
            if (j > 1) {
                dp[i][j] = dp[i][j-1] < dp[i][j] ? dp[i][j-1] : dp[i][j];
            }
            if (A[i][j] > dp[i][j]) {
                dp[i][j] = A[i][j];
            }
        }
    }
    
    k = n + m - 1;
    i = n; j = m;
    while (k > 0) {
        path[k--] = dp[i][j];
        if (i > 1 && j > 1) {
            if (dp[i-1][j] < dp[i][j-1]) {
                i--;
            } else {
                j--;
            }
        } else if (i > 1) {
            i--;
        } else {
            j--;
        }
    }
}

int main() {
    scanf("%lld %lld %lld %lld %lld", &x0, &a, &b, &c, &d);
    scanf("%d %d %d", &n, &m, &q);
    
    init_permutation();
    extra_swap();
    fill_board();
    solve();
    
    for (int i = 1; i <= n + m - 1; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
    
    return 0;
}