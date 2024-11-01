#include <stdio.h>

#define MAX_N 100

int energy[MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &energy[i]);
        energy[i + n] = energy[i]; // 复制一份以处理环形结构
    }

    int max_energy = 0;

    for (int length = 2; length <= n; length++) {
        for (int i = 1; i <= n; i++) {
            int j = (i + length - 1) % n + 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = energy[i] * energy[k + 1] * energy[j + 1] + dp[i][k] + dp[k + 1][j];
                max_energy = (max_energy < dp[i][j]) ? dp[i][j] : max_energy;
            }
        }
    }

    printf("%d\n", max_energy);
    return 0;
}