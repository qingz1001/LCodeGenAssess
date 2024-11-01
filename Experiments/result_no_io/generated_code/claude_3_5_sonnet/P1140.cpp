#include <stdio.h>
#include <string.h>

#define MAX_LEN 101
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int similarity[5][5] = {
    { 5, -1, -2, -1, -3},
    {-1,  5, -3, -2, -4},
    {-2, -3,  5, -2, -2},
    {-1, -2, -2,  5, -1},
    {-3, -4, -2, -1,  0}
};

int char_to_index(char c) {
    switch(c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return 4;
    }
}

int dp[MAX_LEN][MAX_LEN];

int main() {
    int n1, n2;
    char gene1[MAX_LEN], gene2[MAX_LEN];
    
    scanf("%d %s", &n1, gene1);
    scanf("%d %s", &n2, gene2);

    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 0;
            } else if (i == 0) {
                dp[i][j] = dp[i][j-1] + similarity[4][char_to_index(gene2[j-1])];
            } else if (j == 0) {
                dp[i][j] = dp[i-1][j] + similarity[char_to_index(gene1[i-1])][4];
            } else {
                int match = dp[i-1][j-1] + similarity[char_to_index(gene1[i-1])][char_to_index(gene2[j-1])];
                int delete = dp[i-1][j] + similarity[char_to_index(gene1[i-1])][4];
                int insert = dp[i][j-1] + similarity[4][char_to_index(gene2[j-1])];
                dp[i][j] = MAX(match, MAX(delete, insert));
            }
        }
    }

    printf("%d\n", dp[n1][n2]);

    return 0;
}