#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 220
#define MAX_E 500
#define INF -100000000000000LL

typedef long long ll;

typedef struct {
    int from;
    int to;
    ll gain;
} Edge;

int main(){
    int D, P, C, F, S;
    scanf("%d %d %d %d %d", &D, &P, &C, &F, &S);
    
    Edge edges[MAX_E];
    int edge_count = 0;
    
    for(int i=0;i<P;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        edges[edge_count].from = A;
        edges[edge_count].to = B;
        edges[edge_count].gain = (ll)D;
        edge_count++;
    }
    
    for(int i=0;i<F;i++){
        int J, K, T;
        scanf("%d %d %d", &J, &K, &T);
        edges[edge_count].from = J;
        edges[edge_count].to = K;
        edges[edge_count].gain = (ll)D - (ll)T;
        edge_count++;
    }
    
    ll earnings[MAX_C+1];
    for(int i=1;i<=C;i++) earnings[i] = INF;
    earnings[S] = 0;
    
    int flag = 0;
    for(int step=1; step<=C; step++){
        int updated = 0;
        for(int e=0; e<edge_count; e++){
            int u = edges[e].from;
            int v = edges[e].to;
            ll gain = edges[e].gain;
            if(earnings[u] != INF && earnings[u] + gain > earnings[v]){
                earnings[v] = earnings[u] + gain;
                updated = 1;
                if(step == C){
                    flag = 1;
                }
            }
        }
        if(step == C && flag){
            break;
        }
        if(!updated){
            break;
        }
    }
    
    if(flag){
        printf("-1\n");
        return 0;
    }
    
    ll max_earn = 0;
    for(int i=1;i<=C;i++){
        if(earnings[i] > max_earn){
            max_earn = earnings[i];
        }
    }
    
    if(max_earn < 0){
        max_earn = 0;
    }
    
    printf("%lld\n", max_earn);
    
    return 0;
}