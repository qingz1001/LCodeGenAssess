#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_B 500

int main(){
    int A, B;
    scanf("%d %d", &A, &B);
    
    int K[MAX_B][MAX_B];
    for(int i=0;i<B;i++){
        for(int j=0;j<B;j++){
            scanf("%d", &K[i][j]);
        }
    }
    
    int min_cost[MAX_B];
    bool visited_nodes[MAX_B];
    for(int i=0;i<B;i++){
        min_cost[i] = A;
        visited_nodes[i] = false;
    }
    
    long long total_cost = 0;
    for(int i=0;i<B;i++){
        int u = -1;
        int current_min = INT_MAX;
        for(int j=0;j<B;j++){
            if(!visited_nodes[j] && min_cost[j] < current_min){
                current_min = min_cost[j];
                u = j;
            }
        }
        
        if(u == -1){
            break;
        }
        
        visited_nodes[u] = true;
        total_cost += current_min;
        
        for(int v=0;v<B;v++){
            if(!visited_nodes[v] && K[u][v] > 0 && K[u][v] < min_cost[v]){
                min_cost[v] = K[u][v];
            }
        }
    }
    
    printf("%lld\n", total_cost);
    return 0;
}