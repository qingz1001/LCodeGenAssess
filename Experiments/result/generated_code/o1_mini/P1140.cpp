#include <stdio.h>
#include <string.h>

int main(){
    int n1, n2;
    char s1[105], s2[105];
    scanf("%d %s", &n1, s1);
    scanf("%d %s", &n2, s2);
    
    int score_table[5][5] = {
        {5, -1, -2, -1, -3}, // A
        {-1, 5, -3, -2, -4}, // C
        {-2, -3, 5, -2, -2}, // G
        {-1, -2, -2, 5, -1}, // T
        {-3, -4, -2, -1, 0}  // -
    };
    
    int map_char[256];
    map_char['A'] = 0;
    map_char['C'] = 1;
    map_char['G'] = 2;
    map_char['T'] = 3;
    map_char['-'] = 4;
    
    int dp[105][105];
    for(int i=0;i<=n1;i++) {
        for(int j=0;j<=n2;j++) {
            if(i == 0 && j == 0){
                dp[i][j] = 0;
            }
            else if(i == 0){
                dp[i][j] = dp[i][j-1] + score_table[4][map_char[s2[j-1]]];
            }
            else if(j == 0){
                dp[i][j] = dp[i-1][j] + score_table[map_char[s1[i-1]]][4];
            }
            else{
                int match = dp[i-1][j-1] + score_table[map_char[s1[i-1]]][map_char[s2[j-1]]];
                int delete = dp[i-1][j] + score_table[map_char[s1[i-1]]][4];
                int insert = dp[i][j-1] + score_table[4][map_char[s2[j-1]]];
                if(match > delete && match > insert){
                    dp[i][j] = match;
                }
                else if(delete > insert){
                    dp[i][j] = delete;
                }
                else{
                    dp[i][j] = insert;
                }
            }
        }
    }
    
    printf("%d\n", dp[n1][n2]);
    return 0;
}