#include <stdio.h>
#include <string.h>

#define MAX_N 351
#define MAX_M 121

int N, M;
int board[MAX_N];
int cards[5];
int dp[MAX_N][MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &board[i]);
    }
    
    memset(cards, 0, sizeof(cards));
    for (int i = 0; i < M; i++) {
        int card;
        scanf("%d", &card);
        cards[card]++;
    }
    
    memset(dp, -1, sizeof(dp));
    dp[1][0] = board[1];
    
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (dp[i][j] == -1) continue;
            
            for (int k = 1; k <= 4; k++) {
                if (cards[k] > 0 && i + k <= N) {
                    dp[i + k][j + 1] = max(dp[i + k][j + 1], dp[i][j] + board[i + k]);
                }
            }
        }
    }
    
    int result = 0;
    for (int j = 0; j <= M; j++) {
        result = max(result, dp[N][j]);
    }
    
    printf("%d\n", result);
    
    return 0;
}