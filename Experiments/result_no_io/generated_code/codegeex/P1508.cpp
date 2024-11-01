#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int **energy = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        energy[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &energy[i][j]);
        }
    }

    int *dp = (int *)malloc(n * sizeof(int));
    dp[n / 2] = energy[m - 1][n / 2];

    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            int max_energy = energy[i][j];
            if (j > 0) {
                max_energy = (dp[j - 1] > max_energy) ? dp[j - 1] : max_energy;
            }
            if (j < n - 1) {
                max_energy = (dp[j + 1] > max_energy) ? dp[j + 1] : max_energy;
            }
            dp[j] = max_energy + energy[i][j];
        }
    }

    int max_energy = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > max_energy) {
            max_energy = dp[i];
        }
    }

    printf("%d\n", max_energy);

    for (int i = 0; i < m; i++) {
        free(energy[i]);
    }
    free(energy);
    free(dp);

    return 0;
}