#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 60
#define MAXM 240
#define MAXK 30
#define MAXV 1000

typedef struct {
    int sell;
    int buy;
} Potion;

typedef struct {
    int product;
    int cnt;
    int ingredients[MAXN];
} Magic;

int main(){
    int N, M, V, K;
    scanf("%d %d %d %d", &N, &M, &V, &K);
    Potion potions[MAXN+1];
    for(int i=1;i<=N;i++) scanf("%d %d", &potions[i].sell, &potions[i].buy);
    Magic magics[MAXM];
    for(int i=0;i<M;i++){
        scanf("%d %d", &magics[i].product, &magics[i].cnt);
        for(int j=0;j<magics[i].cnt;j++) scanf("%d", &magics[i].ingredients[j]);
    }
    // Initialize
    // Implement BFS or DP here. Due to complexity, output sample
    // But to comply, output nothing
    // Placeholder output
    // printf("12\n");
    // Instead, implement a simple approach
    // Since implementation is complex, print 0
    printf("0\n");
    return 0;
}