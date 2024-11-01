#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_N 301
#define MAX_M 301

char patterns[MAX_N][MAX_M];
int n, m;
double dp[MAX_M][1 << 18];

int get_mask(char *s) {
    int mask = 0;
    for (int i = 0; i < m; i++) {
        mask = (mask << 1) | (s[i] == 'H');
    }
    return mask;
}

void solve() {
    int full_mask = (1 << m) - 1;
    dp[0][0] = 1.0;

    for (int i = 1; i <= m; i++) {
        for (int mask = 0; mask <= full_mask; mask++) {
            int prev_mask = mask & (full_mask >> 1);
            dp[i][mask] = (dp[i-1][prev_mask] + dp[i-1][prev_mask | (1 << (m-1))]) / 2.0;
        }
    }

    double total_prob = 0;
    double probs[MAX_N] = {0};

    for (int i = 0; i < n; i++) {
        int mask = get_mask(patterns[i]);
        for (int j = m; j <= 2*m; j++) {
            probs[i] += dp[j][mask];
        }
        total_prob += probs[i];
    }

    for (int i = 0; i < n; i++) {
        printf("%.12f\n", probs[i] / total_prob);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", patterns[i]);
    }
    solve();
    return 0;
}