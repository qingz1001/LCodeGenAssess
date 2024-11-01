#include <stdio.h>
#include <string.h>

#define MAXN 305
#define EPS 1e-9

int n, m;
char seq[MAXN][MAXN];
double dp[MAXN][1 << MAXN];

void preprocess() {
    for (int i = 0; i < n; i++) {
        int mask = 0;
        for (int j = 0; j < m; j++) {
            if (seq[i][j] == 'H') {
                mask |= (1 << j);
            }
        }
        dp[i][mask] = 1.0 / (1 << m);
    }
}

void solve() {
    double total_prob = 0.0;
    for (int i = 0; i < n; i++) {
        total_prob += dp[i][0];
    }

    for (int i = 0; i < n; i++) {
        double prob = dp[i][0];
        for (int j = 0; j < (1 << m); j++) {
            if ((j & dp[i][j]) != dp[i][j]) continue;
            for (int k = 0; k < n; k++) {
                if (k == i) continue;
                int next_mask = j | dp[k][j];
                if (next_mask == (1 << m)) {
                    prob *= (1 - dp[k][j]);
                } else {
                    prob *= dp[k][next_mask];
                }
            }
        }
        printf("%.10f\n", prob / total_prob);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", seq[i]);
    }

    preprocess();
    solve();

    return 0;
}