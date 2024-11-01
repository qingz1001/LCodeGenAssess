#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 101

int max(int a, int b) {
    return (a > b) ? a : b;
}

int similarity(char *gene1, char *gene2, int len1, int len2) {
    int dp[MAX_LEN][MAX_LEN];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                int match = (gene1[i-1] == gene2[j-1]) ? 5 : -1;
                int insert = -3;
                int delete = -3;
                dp[i][j] = max(max(dp[i-1][j-1] + match, dp[i-1][j] + insert), dp[i][j-1] + delete);
            }
        }
    }

    return dp[len1][len2];
}

int main() {
    int len1, len2;
    char gene1[MAX_LEN], gene2[MAX_LEN];

    scanf("%d %s", &len1, gene1);
    scanf("%d %s", &len2, gene2);

    printf("%d\n", similarity(gene1, gene2, len1, len2));

    return 0;
}