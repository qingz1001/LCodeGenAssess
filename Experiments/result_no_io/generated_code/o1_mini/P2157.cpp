#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001

typedef struct {
    int tree[MAXN];
    int size;
} BIT;

// Initialize BIT
void BIT_init(BIT *bit, int size){
    bit->size = size;
    for(int i=0;i<=size;i++) bit->tree[i]=0;
}

// Update BIT at position idx
void BIT_update(BIT *bit, int idx, int val){
    while(idx <= bit->size){
        bit->tree[idx] += val;
        idx += idx & -idx;
    }
}

// Query prefix sum up to idx
int BIT_query_prefix(BIT *bit, int idx){
    int res = 0;
    while(idx >0){
        res += bit->tree[idx];
        idx -= idx & -idx;
    }
    return res;
}

// Query range sum from l to r
int BIT_query_range(BIT *bit, int l, int r){
    if(l > r) return 0;
    return BIT_query_prefix(bit, r) - BIT_query_prefix(bit, l-1);
}

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        int N;
        scanf("%d", &N);
        int T[MAXN];
        int B[MAXN];
        for(int i=1;i<=N;i++) scanf("%d %d", &T[i], &B[i]);
        
        BIT bit;
        BIT_init(&bit, N);
        int placed[MAXN];
        memset(placed, 0, sizeof(placed));
        long long total_time =0;
        int last_a = -1;
        for(int step=1; step<=N; step++){
            int min_cost = -1;
            int selected_j = -1;
            for(int j=1; j<=N; j++){
                if(!placed[j]){
                    int inv_j = BIT_query_range(&bit, j+1, N);
                    if(inv_j <= B[j]){
                        int cost_j;
                        if(last_a == -1){
                            cost_j = 0;
                        }
                        else{
                            cost_j = T[j] ^ last_a;
                        }
                        if(selected_j == -1 || cost_j < min_cost){
                            min_cost = cost_j;
                            selected_j = j;
                        }
                    }
                }
            }
            if(selected_j == -1){
                // Should not happen as per problem statement
                break;
            }
            if(last_a != -1){
                total_time += (T[selected_j] ^ last_a);
            }
            last_a = T[selected_j];
            placed[selected_j] =1;
            BIT_update(&bit, selected_j, 1);
        }
        printf("%lld\n", total_time);
    }
    return 0;
}