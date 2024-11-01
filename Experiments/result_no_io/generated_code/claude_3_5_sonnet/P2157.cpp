#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1005
#define INF 0x3f3f3f3f

int N;
int T[MAX_N], B[MAX_N];
int dp[MAX_N][8];
int queue[MAX_N], head, tail;

int calc_time(int a, int b) {
    return (a | b) - (a & b);
}

int main() {
    int C;
    scanf("%d", &C);
    
    while (C--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            scanf("%d %d", &T[i], &B[i]);
        }
        
        memset(dp, 0x3f, sizeof(dp));
        dp[1][0] = 0;
        
        for (int i = 2; i <= N; i++) {
            head = 1; tail = 0;
            for (int j = i-1; j > 0; j--) {
                while (head <= tail && queue[head] > j + B[j]) head++;
                while (head <= tail && dp[j][i-j-1] <= dp[queue[tail]][i-queue[tail]-1]) tail--;
                queue[++tail] = j;
                
                if (i-j-1 <= 7) {
                    dp[i][i-j-1] = dp[queue[head]][i-queue[head]-1] + calc_time(T[queue[head]], T[i]);
                }
            }
        }
        
        int ans = INF;
        for (int i = 0; i < 8; i++) {
            if (dp[N][i] < ans) ans = dp[N][i];
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}