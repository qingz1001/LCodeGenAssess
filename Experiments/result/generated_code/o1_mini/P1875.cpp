#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int A, B, C;
} recipe_t;

int N;
int price[1000];
recipe_t recipes[100000];
int M = 0;
int min_cost[1000];
ll count_way[1000];
int sorted_potions[1000];

// Comparator for qsort
int compare_indices(const void* a, const void* b) {
    int idx_a = *((int*)a);
    int idx_b = *((int*)b);
    if (min_cost[idx_a] < min_cost[idx_b])
        return -1;
    else if (min_cost[idx_a] > min_cost[idx_b])
        return 1;
    else
        return 0;
}

int main(){
    // Read N
    if(scanf("%d", &N)!=1){
        return 0;
    }
    // Read prices
    for(int i=0;i<N;i++){
        if(scanf("%d", &price[i])!=1){
            return 0;
        }
    }
    // Read recipes
    while(scanf("%d %d %d", &recipes[M].A, &recipes[M].B, &recipes[M].C)==3){
        M++;
        if(M >= 100000){
            break;
        }
    }
    // Initialize min_cost
    for(int i=0;i<N;i++) min_cost[i] = price[i];
    
    // Compute min_cost using Bellman-Ford-like iterations
    int changed = 1;
    for(int iter=0; iter<N && changed; iter++){
        changed = 0;
        for(int i=0;i<M;i++){
            int A = recipes[i].A;
            int B = recipes[i].B;
            int C = recipes[i].C;
            if (A <0 || A >=N || B <0 || B >=N || C <0 || C >=N) continue;
            if(min_cost[A] + min_cost[B] < min_cost[C]){
                min_cost[C] = min_cost[A] + min_cost[B];
                changed = 1;
            }
        }
    }
    
    // Initialize sorted_potions
    for(int i=0;i<N;i++) sorted_potions[i] = i;
    
    // Sort potions by min_cost ascending
    qsort(sorted_potions, N, sizeof(int), compare_indices);
    
    // Initialize counts
    for(int i=0;i<N;i++) count_way[i] = 0;
    
    for(int i=0;i<N;i++){
        int C = sorted_potions[i];
        if(min_cost[C] == price[C]){
            count_way[C] +=1;
        }
        for(int j=0; j<M; j++){
            if(recipes[j].C == C){
                int A = recipes[j].A;
                int B = recipes[j].B;
                if(min_cost[A] + min_cost[B] == min_cost[C]){
                    count_way[C] += count_way[A] * count_way[B];
                    // Ensure it doesn't exceed 2^63-1 is guaranteed by problem
                }
            }
        }
    }
    
    printf("%d %lld\n", min_cost[0], count_way[0]);
    
    return 0;
}