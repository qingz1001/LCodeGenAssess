#include <stdio.h>
#include <string.h>

#define MAX 128
#define MOD 10007

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Initialize C[k][n] to 0
    int C[MAX][MAX];
    memset(C, 0, sizeof(C));
    C[0][0] = 1;
    
    // Initialize dp_tree
    int dp_tree[MAX];
    memset(dp_tree, 0, sizeof(dp_tree));
    dp_tree[0] = 1;
    
    for(int current_n = 1; current_n <= n; current_n++){
        // Compute C[k][current_n -1] for k=1 to m
        for(int k =1; k <=m; k++){
            int target_n = current_n -1;
            if(target_n <0){
                C[k][target_n] =0;
                continue;
            }
            int temp =0;
            for(int i=1; i <= target_n; i++){
                temp += (dp_tree[i] * C[k-1][target_n -i]) % MOD;
                if(temp >= MOD) temp -= MOD;
            }
            C[k][target_n] = temp % MOD;
        }
        
        // Compute dp_tree[current_n]
        dp_tree[current_n] =0;
        for(int k=0; k <=m; k++){
            if(k ==0 && (current_n -1) ==0){
                dp_tree[current_n] = (dp_tree[current_n] +1) % MOD;
            }
            else if(k >0 && (current_n -1) >=1){
                dp_tree[current_n] = (dp_tree[current_n] + C[k][current_n -1]) % MOD;
            }
        }
    }
    
    printf("%d\n", dp_tree[n] % MOD);
    return 0;
}