#include <stdio.h>
#include <stdlib.h>

#define MAX_K 10000
#define MAX_N 100
#define MAX_M 100
#define MAX_Q 10000

typedef long long ll;

int main(){
    ll x0, a, b, c, d;
    scanf("%lld %lld %lld %lld %lld", &x0, &a, &b, &c, &d);
    int N, M, Q;
    scanf("%d %d %d", &N, &M, &Q);
    int K = N * M;
    ll x[MAX_K +1];
    x[0] = x0;
    for(int i=1;i<=K;i++) {
        x[i] = (a * x[i-1] * x[i-1] + b * x[i-1] + c) % d;
    }
    int T[MAX_K +1];
    for(int i=1;i<=K;i++) T[i] = i;
    for(int i=1;i<=K;i++){
        int pos = (x[i] % i) +1;
        int temp = T[i];
        T[i] = T[pos];
        T[pos] = temp;
    }
    for(int i=0;i<Q;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        int temp = T[u];
        T[u] = T[v];
        T[v] = temp;
    }
    int grid[MAX_N +1][MAX_M +1];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            grid[i][j] = T[(i-1)*M +j];
        }
    }
    // Initialize dp
    int L = N + M -1;
    int dp[MAX_N +1][MAX_M +1][MAX_K +1];
    // Initialize first cell
    dp[1][1][0] = grid[1][1];
    // Fill first row
    for(int j=2;j<=M;j++){
        for(int k=0;k<j-1;k++) dp[1][j][k] = dp[1][j-1][k];
        dp[1][j][j-1] = grid[1][j];
        // Sort
        for(int k=0;k<j;k++){
            for(int l=k+1;l<j;l++){
                if(dp[1][j][k] > dp[1][j][l]){
                    int tmp = dp[1][j][k];
                    dp[1][j][k] = dp[1][j][l];
                    dp[1][j][l] = tmp;
                }
            }
        }
    }
    // Fill first column
    for(int i=2;i<=N;i++){
        for(int k=0;k<i-1;k++) dp[i][1][k] = dp[i-1][1][k];
        dp[i][1][i-1] = grid[i][1];
        // Sort
        for(int k=0;k<i;k++){
            for(int l=k+1;l<i;l++){
                if(dp[i][1][k] > dp[i][1][l]){
                    int tmp = dp[i][1][k];
                    dp[i][1][k] = dp[i][1][l];
                    dp[i][1][l] = tmp;
                }
            }
        }
    }
    // Fill rest
    for(int i=2;i<=N;i++){
        for(int j=2;j<=M;j++){
            // Merge from top
            int top[L];
            for(int k=0;k<(i+j-2);k++) top[k] = dp[i-1][j][k];
            top[i+j-2] = grid[i][j];
            // Sort
            for(int k=0;k<(i+j-1);k++){
                for(int l=k+1;l<(i+j-1);l++){
                    if(top[k] > top[l]){
                        int tmp = top[k];
                        top[k] = top[l];
                        top[l] = tmp;
                    }
                }
            }
            // Merge from left
            int left[L];
            for(int k=0;k<(i+j-2);k++) left[k] = dp[i][j-1][k];
            left[i+j-2] = grid[i][j];
            // Sort
            for(int k=0;k<(i+j-1);k++){
                for(int l=k+1;l<(i+j-1);l++){
                    if(left[k] > left[l]){
                        int tmp = left[k];
                        left[k] = left[l];
                        left[l] = tmp;
                    }
                }
            }
            // Compare top and left
            int flag = 0;
            for(int k=0;k<(i+j-1);k++){
                if(top[k] < left[k]){
                    flag = 1;
                    break;
                }
                else if(top[k] > left[k]){
                    flag = -1;
                    break;
                }
            }
            if(flag == 1){
                for(int k=0;k<(i+j-1);k++) dp[i][j][k] = top[k];
            }
            else{
                for(int k=0;k<(i+j-1);k++) dp[i][j][k] = left[k];
            }
        }
    }
    // Print result
    for(int k=0;k<L;k++){
        printf("%d", dp[N][M][k]);
        if(k != L-1) printf(" ");
    }
    return 0;
}