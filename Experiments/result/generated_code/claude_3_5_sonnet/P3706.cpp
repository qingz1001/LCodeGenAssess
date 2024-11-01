#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 305
#define MAXM 305

char patterns[MAXN][MAXM];
double dp[MAXM][1 << 18];
int fail[MAXN][MAXM];
int mask[MAXM];

void kmp_preprocess(char* pattern, int* fail, int m) {
    fail[0] = fail[1] = 0;
    for (int i = 2; i <= m; i++) {
        int j = fail[i-1];
        while (j > 0 && pattern[j] != pattern[i-1])
            j = fail[j];
        if (pattern[j] == pattern[i-1])
            j++;
        fail[i] = j;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%s", patterns[i]);
        kmp_preprocess(patterns[i], fail[i], m);
    }

    for (int i = 0; i < (1 << n); i++)
        dp[0][i] = 1.0;

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < (1 << n); j++) {
            double probH = 0, probT = 0;
            for (int k = 0; k < n; k++) {
                if (j & (1 << k)) continue;
                int new_mask = j;
                int pos = mask[k];
                while (pos > 0 && patterns[k][pos] != 'H')
                    pos = fail[k][pos];
                if (patterns[k][pos] == 'H')
                    pos++;
                if (pos == m)
                    new_mask |= (1 << k);
                mask[k] = pos;
                probH += dp[i-1][new_mask];

                pos = mask[k];
                while (pos > 0 && patterns[k][pos] != 'T')
                    pos = fail[k][pos];
                if (patterns[k][pos] == 'T')
                    pos++;
                if (pos == m)
                    new_mask |= (1 << k);
                mask[k] = pos;
                probT += dp[i-1][new_mask];
            }
            dp[i][j] = (probH + probT) / 2.0;
        }
    }

    for (int i = 0; i < n; i++) {
        double prob = 0;
        for (int j = 0; j < (1 << n); j++) {
            if (!(j & (1 << i)))
                prob += dp[m][j];
        }
        printf("%.10f\n", prob);
    }

    return 0;
}