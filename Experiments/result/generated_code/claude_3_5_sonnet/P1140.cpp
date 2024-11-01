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

int max_similarity(char *s1, char *s2, int m, int n) {
    int dp[MAX_LEN][MAX_LEN] = {0};
    
    for (int i = 1; i <= m; i++)
        dp[i][0] = dp[i-1][0] + similarity[char_to_index(s1[i-1])][4];
    
    for (int j = 1; j <= n; j++)
        dp[0][j] = dp[0][j-1] + similarity[4][char_to_index(s2[j-1])];
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int match = dp[i-1][j-1] + similarity[char_to_index(s1[i-1])][char_to_index(s2[j-1])];
            int delete = dp[i-1][j] + similarity[char_to_index(s1[i-1])][4];
            int insert = dp[i][j-1] + similarity[4][char_to_index(s2[j-1])];
            dp[i][j] = MAX(match, MAX(delete, insert));
        }
    }
    
    return dp[m][n];
}

int main() {
    int m, n;
    char s1[MAX_LEN], s2[MAX_LEN];
    
    scanf("%d %s", &m, s1);
    scanf("%d %s", &n, s2);
    
    printf("%d\n", max_similarity(s1, s2, m, n));
    
    return 0;
}