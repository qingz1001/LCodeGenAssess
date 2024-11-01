#include <stdio.h>

unsigned long long dp[31][31];
int root_node[31][31];
int pre_order[30];
int index_pre = 0;
int n;
int d[31];

void traverse(int i, int j){
    if(i > j) return;
    int k = root_node[i][j];
    pre_order[index_pre++] = k;
    traverse(i, k-1);
    traverse(k+1, j);
}

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++) {
        scanf("%d", &d[i]);
    }
    for(int len=1; len<=n; len++){
        for(int i=1; i+len-1<=n; i++){
            int j = i + len -1;
            if(i == j){
                dp[i][j] = d[i];
                root_node[i][j] = i;
            }
            else{
                dp[i][j] = 0;
                for(int k=i; k<=j; k++){
                    unsigned long long left = (k-1 >= i) ? dp[i][k-1] : 1;
                    unsigned long long right = (k+1 <= j) ? dp[k+1][j] : 1;
                    unsigned long long current_score = left * right + d[k];
                    if(current_score > dp[i][j]){
                        dp[i][j] = current_score;
                        root_node[i][j] = k;
                    }
                }
            }
        }
    }
    printf("%llu\n", dp[1][n]);
    traverse(1, n);
    for(int i=0;i<index_pre;i++){
        if(i !=0) printf(" ");
        printf("%d", pre_order[i]);
    }
    printf("\n");
    return 0;
}