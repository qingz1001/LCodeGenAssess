#include <stdio.h>
#include <stdlib.h>

long long dp[31][31];
int rootk[31][31];
int d[31];
int pre_order[31];
int pre_index = 0;

void compute_dp(int n){
    for(int len=1; len<=n; len++){
        for(int i=1; i+len-1<=n; i++){
            int j = i + len -1;
            dp[i][j] = -1;
            for(int k=i; k<=j; k++){
                long long left = (k == i) ? 1 : dp[i][k-1];
                long long right = (k == j) ? 1 : dp[k+1][j];
                long long current = left * right + d[k];
                if(current > dp[i][j]){
                    dp[i][j] = current;
                    rootk[i][j] = k;
                }
            }
        }
    }
}

void get_preorder(int i, int j){
    if(i > j) return;
    int k = rootk[i][j];
    pre_order[pre_index++] = k;
    get_preorder(i, k-1);
    get_preorder(k+1, j);
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", &d[i]);
    compute_dp(n);
    get_preorder(1, n);
    printf("%lld\n", dp[1][n]);
    for(int i=0; i<pre_index; i++){
        if(i >0) printf(" ");
        printf("%d", pre_order[i]);
    }
    return 0;
}