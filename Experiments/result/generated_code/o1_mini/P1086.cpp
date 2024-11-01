#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_S 15
#define MAX_MASK (1<<MAX_S)
#define INF 1000000

typedef struct {
    int x;
    int y;
    int p;
} Plant;

int compare(const void *a, const void *b){
    Plant *pa = (Plant*)a;
    Plant *pb = (Plant*)b;
    if(pb->p != pa->p) return pb->p - pa->p;
    else return 0;
}

int main(){
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int grid[M+1][N+1];
    for(int i=1;i<=M;i++) {
        for(int j=1;j<=N;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    Plant temp[400];
    int S=0;
    for(int i=1;i<=M;i++) {
        for(int j=1;j<=N;j++) {
            if(grid[i][j]>0){
                temp[S].x = i;
                temp[S].y = j;
                temp[S].p = grid[i][j];
                S++;
            }
        }
    }
    qsort(temp, S, sizeof(Plant), compare);
    if(S > MAX_S) S = MAX_S;
    Plant plants[MAX_S];
    for(int i=0;i<S;i++) {
        plants[i] = temp[i];
    }
    // Precompute min_move_to_first_row
    int min_move_to_first_row[MAX_S];
    for(int i=0;i<S;i++) {
        int min_dist = INF;
        for(int j=0;j<S;j++) {
            if(plants[j].x == 1){
                int dist = abs(plants[i].x - plants[j].x) + abs(plants[i].y - plants[j].y);
                if(dist < min_dist){
                    min_dist = dist;
                }
            }
        }
        if(plants[i].x ==1){
            min_move_to_first_row[i] =0;
        }
        else{
            min_move_to_first_row[i] = min_dist;
        }
    }
    // Precompute sum_p
    int sum_p[MAX_MASK];
    sum_p[0]=0;
    for(int mask=1; mask<(1<<S); mask++) {
        int last = 0;
        for(int i=0;i<S;i++) {
            if(mask & (1<<i)){
                last = i;
                break;
            }
        }
        sum_p[mask] = sum_p[mask ^ (1<<last)] + plants[last].p;
    }
    // Initialize DP
    int dp[MAX_MASK][MAX_S];
    for(int mask=0; mask<(1<<S); mask++) {
        for(int i=0; i<S; i++) {
            dp[mask][i] = INF;
        }
    }
    for(int i=0;i<S;i++) {
        if(plants[i].x ==1){
            int mask = 1<<i;
            dp[mask][i] = 1 +1; // jump to plant + pick
        }
    }
    // DP transitions
    for(int mask=0; mask<(1<<S); mask++) {
        for(int i=0;i<S;i++) {
            if(mask & (1<<i)) {
                if(dp[mask][i] < INF){
                    for(int j=0; j<S; j++) {
                        if(!(mask & (1<<j))){
                            int new_mask = mask | (1<<j);
                            int move_time = abs(plants[i].x - plants[j].x) + abs(plants[i].y - plants[j].y);
                            int new_time = dp[mask][i] + move_time +1; // move + pick
                            if(new_time < dp[new_mask][j]){
                                dp[new_mask][j] = new_time;
                            }
                        }
                    }
                }
            }
        }
    }
    // Find maximum sum
    int max_sum =0;
    for(int mask=1; mask<(1<<S); mask++) {
        for(int i=0;i<S;i++) {
            if(mask & (1<<i)){
                int total_time;
                if(plants[i].x ==1){
                    total_time = dp[mask][i] +1; // jump back
                }
                else{
                    total_time = dp[mask][i] + min_move_to_first_row[i] +1; // move to first row + jump back
                }
                if(total_time <= K){
                    if(sum_p[mask] > max_sum){
                        max_sum = sum_p[mask];
                    }
                }
            }
        }
    }
    printf("%d\n", max_sum);
    return 0;
}