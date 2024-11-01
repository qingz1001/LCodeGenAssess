#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 51
#define INF 1000000000000LL

typedef long long ll;

ll dp[MAX][MAX][2];
ll pos_arr[MAX];
ll W[MAX];
ll S[MAX];
int main(){
    int n, c;
    scanf("%d %d", &n, &c);
    for(int i=1;i<=n;i++){
        scanf("%lld %lld", &pos_arr[i], &W[i]);
    }
    // Compute prefix sums
    S[0]=0;
    for(int i=1;i<=n;i++) S[i]=S[i-1]+W[i];
    ll total_W = S[n];
    // Initialize DP
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            dp[i][j][0]=INF;
            dp[i][j][1]=INF;
        }
    }
    dp[c][c][0]=0;
    dp[c][c][1]=0;
    // Iterate over number of lamps turned off
    for(int turned=1; turned<n; turned++){
        for(int l=1; l<=c && l<=n; l++){
            for(int r=c; r<=n && r>=l; r++){
                for(int dir=0; dir<=1; dir++){
                    if(dp[l][r][dir] == INF) continue;
                    ll remaining_W = total_W - (S[r] - (l>1? S[l-1] : 0));
                    if(dir ==0){
                        // Move left
                        if(l >1){
                            ll d = pos_arr[l] - pos_arr[l-1];
                            int new_l = l-1;
                            int new_r = r;
                            int new_dir =0;
                            ll new_cost = dp[l][r][dir] + d * remaining_W;
                            if(new_cost < dp[new_l][new_r][new_dir]){
                                dp[new_l][new_r][new_dir] = new_cost;
                            }
                        }
                        // Move right
                        if(r <n){
                            ll d = pos_arr[r+1] - pos_arr[l];
                            int new_l = l;
                            int new_r = r+1;
                            int new_dir =1;
                            ll new_cost = dp[l][r][dir] + d * remaining_W;
                            if(new_cost < dp[new_l][new_r][new_dir]){
                                dp[new_l][new_r][new_dir] = new_cost;
                            }
                        }
                    }
                    if(dir ==1){
                        // Move right
                        if(r <n){
                            ll d = pos_arr[r+1] - pos_arr[r];
                            int new_l = l;
                            int new_r = r+1;
                            int new_dir =1;
                            ll new_cost = dp[l][r][dir] + d * remaining_W;
                            if(new_cost < dp[new_l][new_r][new_dir]){
                                dp[new_l][new_r][new_dir] = new_cost;
                            }
                        }
                        // Move left
                        if(l >1){
                            ll d = pos_arr[r] - pos_arr[l-1];
                            int new_l = l-1;
                            int new_r = r;
                            int new_dir =0;
                            ll new_cost = dp[l][r][dir] + d * remaining_W;
                            if(new_cost < dp[new_l][new_r][new_dir]){
                                dp[new_l][new_r][new_dir] = new_cost;
                            }
                        }
                    }
                }
            }
        }
    }
    ll res = INF;
    if(dp[1][n][0] < res) res = dp[1][n][0];
    if(dp[1][n][1] < res) res = dp[1][n][1];
    printf("%lld\n", res);
}