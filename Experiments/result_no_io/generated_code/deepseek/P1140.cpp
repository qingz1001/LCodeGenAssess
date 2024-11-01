#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 101

int similarity[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, INT_MIN}
};

int max(int a, int b) {
    return a > b ? a : b;
}

int calculate_similarity(char *gene1, char *gene2) {
    int len1 = strlen(gene1);
    int len2 = strlen(gene2);
    int dp[MAX_LEN][MAX_LEN];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 0;
            } else if (i == 0) {
                dp[i][j] = dp[i][j-1] + similarity[4][gene2[j-1] - 'A'];
            } else if (j == 0) {
                dp[i][j] = dp[i-1][j] + similarity[gene1[i-1] - 'A'][4];
            } else {
                dp[i][j] = max(dp[i-1][j-1] + similarity[gene1[i-1] - 'A'][gene2[j-1] - 'A'],
                               max(dp[i-1][j] + similarity[gene1[i-1] - 'A'][4],
                                   dp[i][j-1] + similarity[4][gene2[j-1] - 'A']));
            }
        }
    }

    return dp[len1][len2];
}

int main() {
    int n1, n2;
    char gene1[MAX_LEN], gene2[MAX_LEN];

    scanf("%d %s", &n1, gene1);
    scanf("%d %s", &n2, gene2);

    int result = calculate_similarity(gene1, gene2);
    printf("%d\n", result);

    return 0;
}