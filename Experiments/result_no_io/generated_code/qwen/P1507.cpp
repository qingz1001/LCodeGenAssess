#include <stdio.h>
#include <stdlib.h>

#define MAX_H 401
#define MAX_T 401
#define MAX_K 501

int max_calories(int h, int t, int n, int volumes[], int masses[], int calories[]) {
    int dp[MAX_H][MAX_T];
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= t; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = h; j >= volumes[i]; j--) {
            for (int k = t; k >= masses[i]; k--) {
                dp[j][k] = dp[j][k] > dp[j - volumes[i]][k - masses[i]] + calories[i] ? 
                           dp[j][k] : dp[j - volumes[i]][k - masses[i]] + calories[i];
            }
        }
    }

    return dp[h][t];
}

int main() {
    int h, t, n;
    scanf("%d %d", &h, &t);
    scanf("%d", &n);

    int volumes[n], masses[n], calories[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &volumes[i], &masses[i], &calories[i]);
    }

    printf("%d\n", max_calories(h, t, n, volumes, masses, calories));

    return 0;
}