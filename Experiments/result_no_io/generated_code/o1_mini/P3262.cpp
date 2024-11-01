#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 1024
#define MAXM 513

long long dp_war[MAXN][MAXM];
long long dp_logistic[MAXN][MAXM];
long long w_values[512][10];
long long f_values[512][10];
int n, m;
int total_nodes;
int leaf_start;

int main(){
    scanf("%d %d", &n, &m);
    leaf_start = (1 << (n-1));
    total_nodes = (1 << n) -1;
    int num_leaves = (1 << (n-1));
    // Read w
    for(int i=0;i<num_leaves;i++){
        for(int j=0;j<n-1;j++){
            scanf("%lld", &w_values[i][j]);
        }
    }
    // Read f
    for(int i=0;i<num_leaves;i++){
        for(int j=0;j<n-1;j++){
            scanf("%lld", &f_values[i][j]);
        }
    }
    // Initialize dp_war and dp_logistic
    for(int i=1;i<=total_nodes;i++) {
        for(int k=0;k<=m;k++) {
            dp_war[i][k] = -1e18;
            dp_logistic[i][k] = -1e18;
        }
    }
    // Process leaves
    for(int i=0;i<num_leaves;i++){
        int node = leaf_start + i;
        // Calculate sum_w and sum_f for this leaf
        long long sum_w =0, sum_f=0;
        for(int j=0;j<n-1;j++){
            sum_w += w_values[i][j];
            sum_f += f_values[i][j];
        }
        // If choose war
        if(1 <= m){
            dp_war[node][1] = sum_w;
        }
        // If choose logistics
        dp_logistic[node][0] = sum_f;
    }
    // Process internal nodes
    for(int node=leaf_start-1; node>=1; node--){
        int left = node*2;
        int right = node*2+1;
        for(int k=0;k<=m;k++){
            dp_war[node][k] = -1e18;
            dp_logistic[node][k] = -1e18;
        }
        for(int kl=0; kl<=m; kl++){
            if(dp_war[left][kl] == -1e18) continue;
            for(int kr=0; kr<=m-kl; kr++){
                if(dp_war[right][kr] == -1e18) continue;
                if(dp_war[node][kl+kr] < dp_war[left][kl] + dp_war[right][kr]){
                    dp_war[node][kl+kr] = dp_war[left][kl] + dp_war[right][kr];
                }
            }
        }
        for(int kl=0; kl<=m; kl++){
            if(dp_logistic[left][kl] == -1e18) continue;
            for(int kr=0; kr<=m-kl; kr++){
                if(dp_logistic[right][kr] == -1e18) continue;
                if(dp_logistic[node][kl+kr] < dp_logistic[left][kl] + dp_logistic[right][kr]){
                    dp_logistic[node][kl+kr] = dp_logistic[left][kl] + dp_logistic[right][kr];
                }
            }
        }
        for(int k=0; k<=m; k++){
            long long val_w = dp_war[node][k];
            long long val_l = dp_logistic[node][k];
            if(val_w == -1e18 && val_l == -1e18) continue;
            if(val_w < val_l){
                dp_war[node][k] = val_l;
            }
            else{
                dp_logistic[node][k] = val_w;
            }
            if(dp_war[node][k] < val_l){
                dp_war[node][k] = val_l;
            }
            if(dp_logistic[node][k] < val_w){
                dp_logistic[node][k] = val_w;
            }
        }
    }
    long long result = -1e18;
    for(int k=0; k<=m; k++){
        if(dp_logistic[1][k] > result){
            result = dp_logistic[1][k];
        }
        if(dp_war[1][k] > result){
            result = dp_war[1][k];
        }
    }
    printf("%lld\n", result);
    return 0;
}