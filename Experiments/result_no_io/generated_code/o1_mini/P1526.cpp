#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 101
#define MAX_N 101
#define INF 1000

typedef struct {
    int x;
    int y;
} Point;

int main(){
    int M, n, k;
    scanf("%d %d %d", &M, &n, &k);
    Point weapons[MAX_M];
    for(int i=1;i<=M;i++) {
        scanf("%d %d", &weapons[i].x, &weapons[i].y);
    }
    Point bombs[MAX_N];
    for(int i=1;i<=n;i++) {
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }
    // Precompute can_cover[i][j]
    int can_cover[MAX_M][MAX_M];
    for(int i=1;i<=M;i++) {
        for(int j=i;j<=M;j++) {
            can_cover[i][j] = 0;
            for(int b=1;b<=n;b++) {
                int ok = 1;
                for(int w=i;w<=j;w++) {
                    long long dx = (long long)(bombs[b].x - weapons[w].x);
                    long long dy = (long long)(bombs[b].y - weapons[w].y);
                    if(dx*dx + dy*dy > (long long)k * k){
                        ok = 0;
                        break;
                    }
                }
                if(ok){
                    can_cover[i][j] =1;
                    break;
                }
            }
        }
    }
    // Initialize DP
    int dp[MAX_M];
    dp[M+1] =0;
    for(int i=M;i>=1;i--){
        dp[i] = INF;
        for(int j=i;j<=M;j++){
            if(can_cover[i][j]){
                if(dp[j+1] +1 < dp[i]){
                    dp[i] = dp[j+1] +1;
                }
            }
        }
    }
    printf("%d\n", dp[1]);
    return 0;
}