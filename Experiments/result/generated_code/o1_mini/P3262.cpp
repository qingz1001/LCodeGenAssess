#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 1024
#define MAXM 512
#define INF -(1<<30)

typedef long long ll;

ll w_vals[MAXN][10];
ll f_vals[MAXN][10];
int n, m;
int num_nodes;
int is_leaf[MAXN];
ll dp[MAXN][2][MAXM+1];

int main(){
    scanf("%d %d", &n, &m);
    int num_civilians = 1 << (n-1);
    num_nodes = (1 << n) -1;
    memset(is_leaf, 0, sizeof(is_leaf));
    for(int i=(1<<(n-1)); i<=num_nodes; i++) is_leaf[i]=1;
    // Read w_vals
    for(int i=1;i<=num_civilians;i++){
        int node = (1 << (n-1)) -1 + i;
        for(int j=0; j<n-1; j++) scanf("%lld", &w_vals[node][j]);
    }
    // Read f_vals
    for(int i=1;i<=num_civilians;i++){
        int node = (1 << (n-1)) -1 + i;
        for(int j=0; j<n-1; j++) scanf("%lld", &f_vals[node][j]);
    }

    // Initialize DP
    for(int i=num_nodes;i>=1;i--){
        if(is_leaf[i]){
            // Leaf node: civilian
            // Initialize to -INF
            for(int s=0;s<2;s++) {
                for(int k=0;k<=m;k++) dp[i][s][k] = INF;
            }
            // Assign to war
            if(1 <= m){
                // Contribution: sum w_ij where j is ancestor and assigned to war
                // But we don't know ancestors' assignments, assume 0 here
                // We'll handle contributions in parent nodes
                // So here just mark that this node is in war, k=1
                dp[i][1][1] = 0;
            }
            // Assign to farm
            // Similar handling
            dp[i][0][0] = 0;
        }
        else{
            // Internal node: noble
            // Initialize to -INF
            for(int s=0;s<2;s++) {
                for(int k=0;k<=m;k++) dp[i][s][k] = INF;
            }
            // Get children
            int left = i*2;
            int right = i*2+1;
            // Iterate over possible states for current node
            for(int s=0;s<2;s++){
                // Iterate over possible k
                for(int kl=0; kl<=m; kl++){
                    for(int kr=0; kr<=m-kl; kr++){
                        if(dp[left][0][kl] == INF && dp[left][1][kl] == INF) continue;
                        if(dp[right][0][kr] == INF && dp[right][1][kr] == INF) continue;
                        // For left child
                        for(int sl=0; sl<2; sl++){
                            if(dp[left][sl][kl] == INF) continue;
                            // For right child
                            for(int sr=0; sr<2; sr++){
                                if(dp[right][sr][kr] == INF) continue;
                                // Total k
                                int total_k = kl + kr;
                                if(total_k > m) continue;
                                // Calculate contribution
                                ll contrib = 0;
                                if(s == 1){
                                    // Current node is war
                                    // Add w_ij from left and right if they are in war
                                    if(left <= num_nodes){
                                        contrib += dp[left][sl][kl];
                                        // Assuming child's contribution is already handled
                                    }
                                    if(right <= num_nodes){
                                        contrib += dp[right][sr][kr];
                                    }
                                }
                                else{
                                    // Current node is logistics
                                    // Add f_ij from left and right if they are in farm
                                    if(left <= num_nodes){
                                        contrib += dp[left][sl][kl];
                                    }
                                    if(right <= num_nodes){
                                        contrib += dp[right][sr][kr];
                                    }
                                }
                                if(contrib > dp[i][s][total_k]){
                                    dp[i][s][total_k] = contrib;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Find maximum
    ll res = INF;
    for(int s=0;s<2;s++){
        for(int k=0;k<=m;k++){
            if(dp[1][s][k] > res){
                res = dp[1][s][k];
            }
        }
    }
    printf("%lld\n", res);
}