#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of monsters
#define MAXN 200005
// Maximum sum of R_i
#define MAX_SUM_R 1000005

typedef unsigned long long ull;

int main(){
    int N;
    scanf("%d", &N);

    // Arrays to store S, K
    ull S[MAXN];
    ull K_val[MAXN];

    // For R_list
    int *R_ids = (int*)malloc(sizeof(int) * MAX_SUM_R);
    int R_start[MAXN];
    int R_len[MAXN];
    int R_ptr = 0;

    // For reverse dependencies
    int *RD_ids = (int*)malloc(sizeof(int) * MAX_SUM_R);
    int RD_start[MAXN];
    int RD_len_arr[MAXN];
    int RD_ptr = 0;

    // Read all data
    for(int k=1; k<=N; k++){
        ull S_k, K_k;
        int R_i;
        scanf("%llu %llu %d", &S_k, &K_k, &R_i);
        S[k] = S_k;
        K_val[k] = K_k;
        R_start[k] = R_ptr;
        R_len[k] = R_i;
        for(int r=0; r<R_i; r++){
            int j;
            scanf("%d", &j);
            R_ids[R_ptr++] = j;
            RD_ids[RD_ptr++] = k;
        }
        RD_start[k] = 0;
        RD_len_arr[k] = 0;
    }

    // Build reverse_dependencies
    // First, count how many reverse dependencies each monster has
    memset(RD_len_arr, 0, sizeof(int)*(N+1));
    for(int r=0; r<R_ptr; r++){
        int j = R_ids[r];
        RD_len_arr[j]++;
    }

    // Allocate space for reverse dependencies
    int *reverse_dependencies = (int*)malloc(sizeof(int) * RD_ptr);
    // Reset RD_len_arr to use as current index
    memset(RD_len_arr, 0, sizeof(int)*(N+1));
    for(int r=0; r<R_ptr; r++){
        int j = R_ids[r];
        int k = RD_ids[r];
        reverse_dependencies[j * MAXN + RD_len_arr[j]] = k;
        RD_len_arr[j]++;
    }

    // Initialize sum_cost and cost
    ull *sum_cost = (ull*)malloc(sizeof(ull) * (N+1));
    ull *cost = (ull*)malloc(sizeof(ull) * (N+1));

    for(int k=1; k<=N; k++){
        ull sc = 0;
        for(int r=0; r<R_len[k]; r++){
            int j = R_ids[R_start[k] + r];
            sc += K_val[j];
        }
        sum_cost[k] = sc;
        cost[k] = K_val[k];
    }

    // Initialize queue
    int *queue = (int*)malloc(sizeof(int) * (N+1));
    int front = 0, rear = 0;

    // Initial pass to update cost and enqueue
    for(int k=1; k<=N; k++){
        ull total = S[k] + sum_cost[k];
        if(total < cost[k]){
            cost[k] = total;
            queue[rear++] = k;
        }
    }

    // Process the queue
    while(front < rear){
        int k = queue[front++];
        // For each monster that depends on k
        int dep_count = RD_len_arr[k];
        for(int d=0; d<dep_count; d++){
            int dependent = reverse_dependencies[k * MAXN + d];
            // Update sum_cost[dependent] by (new_cost[k] - old_cost[k])
            // Since cost[k] was updated to a lower value, (new_cost[k] - old_cost[k]) < 0
            ull old_sum = sum_cost[dependent];
            // Find all j in R_list[dependent] and sum_cost was already maintained
            // So we need to subtract the old K[j] and add the new cost[j]
            // But to simplify, since we have cost[j] already updated,
            // and we already have sum_cost[dependent] as sum cost[j]
            // Thus, no action is needed here because sum_cost[dependent] was already updated
            // However, to track changes, we need to adjust sum_cost
            // To do it correctly, we need to know the change in cost[k]
            // But since we don't store old_cost, we need to keep it
            // Alternative approach: track the delta when updating cost[k]
            // To implement correctly, let's adjust the approach
            // Recompute sum_cost[dependent]
            ull new_sum = 0;
            for(int r=0; r<R_len[dependent]; r++){
                int j = R_ids[R_start[dependent] + r];
                new_sum += cost[j];
            }
            if(S[dependent] + new_sum < cost[dependent]){
                cost[dependent] = S[dependent] + new_sum;
                queue[rear++] = dependent;
            }
        }
    }

    // Output the cost for monster 1
    printf("%llu\n", cost[1]);

    // Free allocated memory
    free(R_ids);
    free(RD_ids);
    free(reverse_dependencies);
    free(sum_cost);
    free(cost);
    free(queue);

    return 0;
}