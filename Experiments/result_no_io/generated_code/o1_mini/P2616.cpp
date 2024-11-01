#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_POSITIONS 102
#define MAX_K 101
#define INF 1000000000

typedef struct {
    int x;
    int f;
    int c;
} Store;

int compare(const void* a, const void* b){
    Store* sa = (Store*)a;
    Store* sb = (Store*)b;
    if(sa->x != sb->x) return sa->x - sb->x;
    return sa->c - sb->c;
}

int main(){
    int N, E, K;
    scanf("%d %d %d", &N, &E, &K);
    Store stores[N];
    for(int i=0;i<N;i++) {
        scanf("%d %d %d", &stores[i].x, &stores[i].f, &stores[i].c);
    }
    qsort(stores, N, sizeof(Store), compare);
    
    // Collect unique positions
    int pos[MAX_POSITIONS];
    int store_start[MAX_POSITIONS];
    int store_count[MAX_POSITIONS];
    int num_pos = 0;
    pos[num_pos] = 0;
    store_start[num_pos] = 0;
    store_count[num_pos] = 0;
    num_pos++;
    for(int i=0;i<N;i++){
        if(stores[i].x != pos[num_pos-1]){
            pos[num_pos] = stores[i].x;
            store_start[num_pos] = i;
            store_count[num_pos] = 1;
            num_pos++;
        }
        else{
            store_count[num_pos-1]++;
        }
    }
    pos[num_pos] = E;
    store_start[num_pos] = N;
    store_count[num_pos] = 0;
    num_pos++;
    
    // Initialize DP
    int dp[MAX_POSITIONS][MAX_K];
    for(int i=0;i<num_pos;i++) {
        for(int j=0;j<=K;j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    
    for(int i=0;i<num_pos-1;i++){
        int distance = pos[i+1] - pos[i];
        // Compute min_cost for buying at position i
        int max_buy = 0;
        for(int s=0;s<store_count[i];s++) {
            max_buy += stores[store_start[i]+s].f;
        }
        if(max_buy > K) max_buy = K;
        int min_cost[MAX_K];
        for(int a=0;a<=K;a++) min_cost[a] = INF;
        min_cost[0] = 0;
        for(int s=0;s<store_count[i];s++){
            int f = stores[store_start[i]+s].f;
            int c = stores[store_start[i]+s].c;
            for(int a=K; a>=0; a--){
                if(min_cost[a] < INF){
                    for(int b=1; b<=f && a+b<=K; b++){
                        if(min_cost[a] + b * c < min_cost[a+b]){
                            min_cost[a+b] = min_cost[a] + b * c;
                        }
                    }
                }
            }
        }
        for(int j=0; j<=K; j++){
            if(dp[i][j] < INF){
                for(int a=0; a<=K-j && a <= max_buy; a++){
                    if(min_cost[a] < INF){
                        int new_j = j + a;
                        int cost = dp[i][j] + min_cost[a] + distance * new_j;
                        if(cost < dp[i+1][new_j]){
                            dp[i+1][new_j] = cost;
                        }
                    }
                }
            }
        }
    }
    
    int result = INF;
    for(int j=K; j<=K; j++){
        if(dp[num_pos-1][j] < result){
            result = dp[num_pos-1][j];
        }
    }
    printf("%d\n", result);
    return 0;
}