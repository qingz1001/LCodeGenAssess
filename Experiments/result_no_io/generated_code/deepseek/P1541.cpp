#include <stdio.h>
#include <stdlib.h>

#define MAXN 351
#define MAXM 121
#define MAXC 41

int dp[MAXC][MAXC][MAXC][MAXC];
int score[MAXN];
int card[5];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &score[i]);
    }
    
    for (int i = 0; i < M; i++) {
        int b;
        scanf("%d", &b);
        card[b]++;
    }
    
    for (int c1 = 0; c1 <= card[1]; c1++) {
        for (int c2 = 0; c2 <= card[2]; c2++) {
            for (int c3 = 0; c3 <= card[3]; c3++) {
                for (int c4 = 0; c4 <= card[4]; c4++) {
                    int pos = 1 + c1 * 1 + c2 * 2 + c3 * 3 + c4 * 4;
                    int current_score = dp[c1][c2][c3][c4];
                    
                    if (c1 > 0) {
                        dp[c1][c2][c3][c4] = max(dp[c1][c2][c3][c4], dp[c1 - 1][c2][c3][c4] + score[pos]);
                    }
                    if (c2 > 0) {
                        dp[c1][c2][c3][c4] = max(dp[c1][c2][c3][c4], dp[c1][c2 - 1][c3][c4] + score[pos]);
                    }
                    if (c3 > 0) {
                        dp[c1][c2][c3][c4] = max(dp[c1][c2][c3][c4], dp[c1][c2][c3 - 1][c4] + score[pos]);
                    }
                    if (c4 > 0) {
                        dp[c1][c2][c3][c4] = max(dp[c1][c2][c3][c4], dp[c1][c2][c3][c4 - 1] + score[pos]);
                    }
                }
            }
        }
    }
    
    printf("%d\n", dp[card[1]][card[2]][card[3]][card[4]] + score[1]);
    
    return 0;
}