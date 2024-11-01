#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_P 200001

typedef struct {
    int t;
    int g;
    int m;
} Order;

typedef struct {
    long long prod;
    int income;
} State;

int compare_orders(const void *a, const void *b){
    Order *oa = (Order *)a;
    Order *ob = (Order *)b;
    if (oa->t != ob->t)
        return oa->t - ob->t;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Order orders[n];
    for(int i=0;i<n;i++) scanf("%d %d %d", &orders[i].t, &orders[i].g, &orders[i].m);
    qsort(orders, n, sizeof(Order), compare_orders);
    // Collect unique times
    int unique_times[n+1];
    int count =0;
    unique_times[count++] =0;
    for(int i=0;i<n;i++) {
        if(i==0 || orders[i].t != orders[i-1].t){
            unique_times[count++] = orders[i].t;
        }
    }
    int total_times = count;
    // Group orders by time
    int group_indices[total_times];
    memset(group_indices, 0, sizeof(group_indices));
    int current =0;
    for(int i=0;i<n;i++) {
        if(i==0 || orders[i].t != orders[i-1].t){
            current++;
        }
        group_indices[current-1]++;
    }
    // Create array of orders per group
    Order *group_orders[total_times];
    int idx =0;
    for(int i=0;i<total_times;i++){
        group_orders[i] = (Order*)malloc(group_indices[i]*sizeof(Order));
        for(int j=0;j<group_indices[i];j++) {
            group_orders[i][j] = orders[idx++];
        }
    }
    // Initialize DP
    State *current_dp = (State*)malloc(MAX_P * sizeof(State));
    State *next_dp = (State*)malloc(MAX_P * sizeof(State));
    for(int i=0;i<MAX_P;i++) {
        current_dp[i].income = -1;
        current_dp[i].prod = 0;
    }
    current_dp[1].income =0;
    current_dp[1].prod =0;
    int last_t =0;
    for(int i=1;i<total_times;i++){
        int ti = unique_times[i];
        int dt = ti - last_t;
        last_t = ti;
        int m = group_indices[i];
        // Precompute all subsets
        int subset_count =1<<m;
        int *sum_g = (int*)malloc(subset_count * sizeof(int));
        int *sum_m = (int*)malloc(subset_count * sizeof(int));
        for(int mask=0; mask<subset_count; mask++){
            sum_g[mask]=0;
            sum_m[mask]=0;
            for(int j=0; j<m; j++) {
                if(mask & (1<<j)){
                    sum_g[mask] += group_orders[i][j].g;
                    sum_m[mask] += group_orders[i][j].m;
                }
            }
        }
        // Initialize next_dp
        for(int p=0; p<MAX_P; p++) {
            next_dp[p].income = -1;
            next_dp[p].prod =0;
        }
        // Iterate through current_dp
        for(int p_prev=0; p_prev < MAX_P; p_prev++) {
            if(current_dp[p_prev].income == -1) continue;
            long long prod_prev = current_dp[p_prev].prod;
            int income_prev = current_dp[p_prev].income;
            for(int mask=0; mask<subset_count; mask++) {
                int required_g = sum_g[mask];
                int gained_m = sum_m[mask];
                // Find minimal k
                int k;
                for(k=0; k<=dt; k++) {
                    long long produced = (long long)(dt -k)*(p_prev +k);
                    if(prod_prev + produced >= required_g) break;
                }
                if(k > dt) continue;
                int p_new = p_prev + k;
                if(p_new >= MAX_P) continue;
                long long prod_new = prod_prev + (long long)(dt -k)*(p_prev +k) - required_g;
                if(prod_new <0) continue;
                int income_new = income_prev + gained_m;
                if(income_new > next_dp[p_new].income){
                    next_dp[p_new].income = income_new;
                    next_dp[p_new].prod = prod_new;
                }
                else if(income_new == next_dp[p_new].income && prod_new > next_dp[p_new].prod){
                    next_dp[p_new].prod = prod_new;
                }
            }
        }
        // Free subset sums
        free(sum_g);
        free(sum_m);
        // Swap dp
        State *temp = current_dp;
        current_dp = next_dp;
        next_dp = temp;
    }
    // Find maximum income
    int max_income =0;
    for(int p=0; p<MAX_P; p++) {
        if(current_dp[p].income > max_income){
            max_income = current_dp[p].income;
        }
    }
    printf("%d", max_income);
    // Free memory
    for(int i=0;i<total_times;i++) free(group_orders[i]);
    free(group_orders);
    free(current_dp);
    free(next_dp);
    return 0;
}