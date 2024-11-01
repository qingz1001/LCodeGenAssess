#include <stdio.h>
#include <string.h>

int main(){
    int n1, n2;
    char s1[105], s2[105];
    // Read first line
    scanf("%d %s", &n1, s1);
    // Read second line
    scanf("%d %s", &n2, s2);
    // Scoring table
    int score[5][5] = {
        {5, -1, -2, -1, -3},
        {-1,5,-3,-2,-4},
        {-2,-3,5,-2,-2},
        {-1,-2,-2,5,-1},
        {-3,-4,-2,-1,0}
    };
    // Function to map character to index
    auto char_to_idx = [](char c) -> int {
        switch(c){
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            case 'T': return 3;
            case '-': return 4;
            default: return 4;
        }
    };
    // Initialize DP table
    int dp[101][101];
    memset(dp, 0, sizeof(dp));
    for(int i=1;i<=n1;i++) dp[i][0] = dp[i-1][0] + score[char_to_idx(s1[i-1])][4];
    for(int j=1;j<=n2;j++) dp[0][j] = dp[0][j-1] + score[4][char_to_idx(s2[j-1])];
    // Fill DP table
    for(int i=1;i<=n1;i++){
        for(int j=1;j<=n2;j++){
            int match = dp[i-1][j-1] + score[char_to_idx(s1[i-1])][char_to_idx(s2[j-1])];
            int gap1 = dp[i-1][j] + score[char_to_idx(s1[i-1])][4];
            int gap2 = dp[i][j-1] + score[4][char_to_idx(s2[j-1])];
            if(match > gap1 && match > gap2) dp[i][j] = match;
            else if(gap1 > gap2) dp[i][j] = gap1;
            else dp[i][j] = gap2;
        }
    }
    printf("%d", dp[n1][n2]);
    return 0;
}