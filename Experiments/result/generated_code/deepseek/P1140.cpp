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

int getIndex(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return 4;
    }
}

int main() {
    int n1, n2;
    char gene1[MAX_LEN], gene2[MAX_LEN];
    int dp[MAX_LEN][MAX_LEN];

    scanf("%d %s", &n1, gene1);
    scanf("%d %s", &n2, gene2);

    dp[0][0] = 0;
    for (int i = 1; i <= n1; i++) {
        dp[i][0] = dp[i-1][0] + similarity[getIndex(gene1[i-1])][4];
    }
    for (int j = 1; j <= n2; j++) {
        dp[0][j] = dp[0][j-1] + similarity[4][getIndex(gene2[j-1])];
    }

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            int match = dp[i-1][j-1] + similarity[getIndex(gene1[i-1])][getIndex(gene2[j-1])];
            int gapGene1 = dp[i-1][j] + similarity[getIndex(gene1[i-1])][4];
            int gapGene2 = dp[i][j-1] + similarity[4][getIndex(gene2[j-1])];
            dp[i][j] = max(match, max(gapGene1, gapGene2));
        }
    }

    printf("%d\n", dp[n1][n2]);

    return 0;
}