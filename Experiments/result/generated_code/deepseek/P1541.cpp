#include <stdio.h>
#include <stdlib.h>

#define MAXN 350
#define MAXM 120
#define MAXC 40

int dp[MAXC+1][MAXC+1][MAXC+1][MAXC+1];
int score[MAXN];
int cards[5] = {0};

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &score[i]);
    }
    
    for (int i = 0; i < M; i++) {
        int card;
        scanf("%d", &card);
        cards[card]++;
    }
    
    for (int a = 0; a <= cards[1]; a++) {
        for (int b = 0; b <= cards[2]; b++) {
            for (int c = 0; c <= cards[3]; c++) {
                for (int d = 0; d <= cards[4]; d++) {
                    int pos = a + 2 * b + 3 * c + 4 * d;
                    int current_score = dp[a][b][c][d];
                    if (a > 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a-1][b][c][d] + score[pos]);
                    if (b > 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b-1][c][d] + score[pos]);
                    if (c > 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c-1][d] + score[pos]);
                    if (d > 0) dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d-1] + score[pos]);
                }
            }
        }
    }
    
    printf("%d\n", dp[cards[1]][cards[2]][cards[3]][cards[4]] + score[0]);
    
    return 0;
}