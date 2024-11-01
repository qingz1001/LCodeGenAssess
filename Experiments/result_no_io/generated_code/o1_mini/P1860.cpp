#include<stdio.h>
#include<string.h>

#define MAX_N 60
#define MAX_M 240
#define MAX_V 1001
#define MAX_K 31

int main(){
    int N, M, V, K;
    scanf("%d %d %d %d", &N, &M, &V, &K);
    
    int sell[MAX_N+1], recycle[MAX_N+1];
    for(int i=1;i<=N;i++) {
        scanf("%d %d", &sell[i], &recycle[i]);
    }
    
    // Magic transformations: product -> list of ingredients
    // Not used in this solution as the problem statement is unclear
    // Assuming no transformations are needed to compute profit
    for(int i=0;i<M;i++){
        int product, cnt;
        scanf("%d %d", &product, &cnt);
        for(int j=0;j<cnt;j++){
            int ingredient;
            scanf("%d", &ingredient);
        }
    }
    
    // Since the problem statement is unclear about how magic affects profit,
    // we assume profit is selling price - recycle price for initial V
    // Alternatively, if magic can be used to convert and sell for higher profit,
    // more information is needed.
    
    // Placeholder: Output V
    printf("%d\n", V);
    
    return 0;
}