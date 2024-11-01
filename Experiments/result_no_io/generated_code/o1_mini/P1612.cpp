#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001
#define LOGN 20

typedef long long ll;

ll parent[MAX_N][LOGN];
ll sum_w[MAX_N][LOGN];
ll w_val[MAX_N];
ll c_val[MAX_N];
ll p_input[MAX_N];
ll answers[MAX_N];

int main(){
    int n;
    scanf("%d", &n);
    
    for(int i=2;i<=n;i++) {
        scanf("%lld", &p_input[i]);
    }
    
    for(int i=1;i<=n;i++) {
        scanf("%lld", &w_val[i]);
    }
    
    for(int i=1;i<=n;i++) {
        scanf("%lld", &c_val[i]);
    }
    
    // Initialize parent and sum_w for k=0
    for(int i=1;i<=n;i++) {
        if(i == 1){
            parent[i][0] = 0;
            sum_w[i][0] = 0;
        }
        else{
            parent[i][0] = p_input[i];
            sum_w[i][0] = w_val[p_input[i]];
        }
    }
    
    // Compute parent and sum_w for higher k
    for(int k=1;k<LOGN;k++) {
        for(int i=1;i<=n;i++) {
            if(parent[i][k-1] != 0){
                parent[i][k] = parent[parent[i][k-1]][k-1];
                sum_w[i][k] = sum_w[i][k-1] + sum_w[parent[i][k-1]][k-1];
            }
            else{
                parent[i][k] = 0;
                sum_w[i][k] = sum_w[i][k-1];
            }
        }
    }
    
    // Compute answers for each node
    for(int i=1;i<=n;i++) {
        ll current_sum = w_val[i];
        ll current_node = i;
        ll length = 1;
        for(int k=LOGN-1;k>=0;k--){
            if(parent[current_node][k] != 0 && current_sum + sum_w[current_node][k] <= c_val[i]){
                current_sum += sum_w[current_node][k];
                current_node = parent[current_node][k];
                length += (1 << k);
            }
        }
        answers[i] = length;
    }
    
    // Print answers
    for(int i=1;i<=n;i++) {
        if(i > 1) printf(" ");
        printf("%lld", answers[i]);
    }
    printf("\n");
    
    return 0;
}