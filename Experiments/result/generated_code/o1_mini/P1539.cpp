#include <stdio.h>
#include <string.h>

#define MAX_M 15
#define MAX_N 15
#define MOD 10007

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[MAX_N][MAX_M+1];
    for(int i=0;i<n;i++) scanf("%s", grid[i]);
    
    int must_one[MAX_N];
    int must_zero[MAX_N];
    for(int i=0;i<n;i++){
        must_one[i]=0;
        must_zero[i]=0;
        for(int j=0;j<m;j++){
            if(grid[i][j]=='1') must_one[i] |= (1<<j);
            if(grid[i][j]=='0') must_zero[i] |= (1<<j);
        }
    }
    
    int dp_prev[1<<MAX_M];
    int dp_curr[1<<MAX_M];
    memset(dp_prev, 0, sizeof(dp_prev));
    dp_prev[0] = 1;
    
    for(int row=0; row<n; row++){
        memset(dp_curr, 0, sizeof(dp_curr));
        for(int prev=0; prev<(1<<m); prev++){
            if(dp_prev[prev]==0) continue;
            for(int curr=0; curr<(1<<m); curr++){
                // Check must_one and must_zero
                if( (curr & must_one[row]) != must_one[row]) continue;
                if( (curr & must_zero[row]) !=0 ) continue;
                // Check no two adjacent 1's in current
                if( (curr & (curr <<1)) !=0 ) continue;
                // Check no vertical adjacency
                if( (curr & prev) !=0 ) continue;
                dp_curr[curr] = (dp_curr[curr] + dp_prev[prev]) % MOD;
            }
        }
        // Swap
        for(int s=0; s<(1<<m); s++) dp_prev[s] = dp_curr[s];
    }
    
    int result=0;
    for(int s=0; s<(1<<m); s++) result = (result + dp_prev[s]) % MOD;
    printf("%d\n", result);
}