#include <stdio.h>
#include <string.h>

#define INF 1000000000
#define MIN(a,b) ((a)<(b)?(a):(b))

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Case 1: room 0 is occupied
    int dp1[m][n+1][2];
    for(int i=0;i<m;i++) {
        for(int j=0;j<=n;j++) {
            for(int k=0;k<2;k++) {
                dp1[i][j][k] = INF;
            }
        }
    }
    dp1[0][1][1] = 0;
    
    for(int pos=1; pos<m; pos++) {
        for(int cnt=0; cnt<=n; cnt++) {
            for(int prev=0; prev<2; prev++) {
                if(dp1[pos-1][cnt][prev] == INF) continue;
                // Option 1: not place at pos
                if(dp1[pos][cnt][0] > dp1[pos-1][cnt][prev]){
                    dp1[pos][cnt][0] = dp1[pos-1][cnt][prev];
                }
                // Option 2: place at pos
                if(cnt < n){
                    int new_cnt = cnt + 1;
                    int add_anger = prev ? 1 : 0;
                    if(dp1[pos][new_cnt][1] > dp1[pos-1][cnt][prev] + add_anger){
                        dp1[pos][new_cnt][1] = dp1[pos-1][cnt][prev] + add_anger;
                    }
                }
            }
        }
    }
    
    int min1 = INF;
    if(n >=1){
        if(dp1[m-1][n][1] != INF){
            min1 = dp1[m-1][n][1] + 1; // adjacency between last and first
        }
    }
    if(dp1[m-1][n][0] != INF){
        if(dp1[m-1][n][0] < min1){
            min1 = dp1[m-1][n][0];
        }
    }
    
    // Case 2: room 0 is not occupied
    int dp2[m][n+1][2];
    for(int i=0;i<m;i++) {
        for(int j=0;j<=n;j++) {
            for(int k=0;k<2;k++) {
                dp2[i][j][k] = INF;
            }
        }
    }
    dp2[0][0][0] = 0;
    
    for(int pos=1; pos<m; pos++) {
        for(int cnt=0; cnt<=n; cnt++) {
            for(int prev=0; prev<2; prev++) {
                if(dp2[pos-1][cnt][prev] == INF) continue;
                // Option 1: not place at pos
                if(dp2[pos][cnt][0] > dp2[pos-1][cnt][prev]){
                    dp2[pos][cnt][0] = dp2[pos-1][cnt][prev];
                }
                // Option 2: place at pos
                if(cnt < n){
                    int new_cnt = cnt + 1;
                    int add_anger = prev ? 1 : 0;
                    if(dp2[pos][new_cnt][1] > dp2[pos-1][cnt][prev] + add_anger){
                        dp2[pos][new_cnt][1] = dp2[pos-1][cnt][prev] + add_anger;
                    }
                }
            }
        }
    }
    
    int min2 = INF;
    if(dp2[m-1][n][0] != INF){
        min2 = dp2[m-1][n][0];
    }
    if(dp2[m-1][n][1] != INF){
        min2 = MIN(min2, dp2[m-1][n][1]);
    }
    
    int answer = INF;
    if(min1 < answer){
        answer = min1;
    }
    if(min2 < answer){
        answer = min2;
    }
    printf("%d\n", answer);
    return 0;
}