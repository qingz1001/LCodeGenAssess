#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t T;
    int64_t A;
    int64_t B;
    int64_t C;
    int64_t D;
    int64_t dp;
} Customer1;

typedef struct {
    int64_t u;
    int64_t v;
    int64_t dp;
} Customer2;

int cmp_T(const void *a, const void *b) {
    Customer1 *ca = (Customer1*)a;
    Customer1 *cb = (Customer1*)b;
    if (ca->T != cb->T)
        return (ca->T < cb->T) ? -1 : 1;
    return 0;
}

int cmp_u_v(const void *a, const void *b) {
    Customer2 *ca = (Customer2*)a;
    Customer2 *cb = (Customer2*)b;
    if (ca->u != cb->u)
        return (ca->u > cb->u) ? -1 : 1;
    if (ca->v != cb->v)
        return (ca->v > cb->v) ? -1 : 1;
    return 0;
}

int main(){
    int N, Q;
    scanf("%d %d", &N, &Q);
    Customer1 *customers1 = (Customer1*)malloc(N * sizeof(Customer1));
    for(int i=0;i<N;i++){
        scanf("%lld %lld %lld %lld", &customers1[i].T, &customers1[i].A, &customers1[i].B, &customers1[i].C);
        customers1[i].D = (customers1[i].A > customers1[i].B) ? (customers1[i].A - customers1[i].B) : (customers1[i].B - customers1[i].A);
    }
    qsort(customers1, N, sizeof(Customer1), cmp_T);
    // Compute dp
    for(int i=N-1;i>=0;i--){
        customers1[i].dp = customers1[i].C * customers1[i].D;
        for(int j=i+1; j<N; j++){
            int64_t travel_time = (customers1[j].A > customers1[i].B) ? (customers1[j].A - customers1[i].B) : (customers1[i].B - customers1[j].A);
            if(customers1[j].T >= customers1[i].T + customers1[i].D + travel_time){
                if(customers1[i].dp < customers1[i].C * customers1[i].D + customers1[j].dp){
                    customers1[i].dp = customers1[i].C * customers1[i].D + customers1[j].dp;
                }
            }
        }
    }
    // Prepare sorted_customers
    Customer2 *sorted_customers = (Customer2*)malloc(N * sizeof(Customer2));
    for(int i=0;i<N;i++){
        sorted_customers[i].u = customers1[i].T + customers1[i].A;
        sorted_customers[i].v = customers1[i].T - customers1[i].A;
        sorted_customers[i].dp = customers1[i].dp;
    }
    qsort(sorted_customers, N, sizeof(Customer2), cmp_u_v);
    // Build max_dp
    int64_t *max_dp = (int64_t*)malloc(N * sizeof(int64_t));
    max_dp[0] = sorted_customers[0].dp;
    for(int i=1;i<N;i++){
        if(sorted_customers[i].dp > max_dp[i-1]){
            max_dp[i] = sorted_customers[i].dp;
        }
        else{
            max_dp[i] = max_dp[i-1];
        }
    }
    // Process queries
    for(int q=0; q<Q; q++){
        int64_t P, X;
        scanf("%lld %lld", &P, &X);
        int64_t s_j = P + X;
        int64_t r_j = P - X;
        // Binary search for k where u_i < s_j
        int low = 0, high = N;
        while(low < high){
            int mid = (low + high) / 2;
            if(sorted_customers[mid].u >= s_j){
                low = mid +1;
            }
            else{
                high = mid;
            }
        }
        int k = low;
        if(k ==0){
            printf("0\n");
            continue;
        }
        // Binary search for p where v_i < r_j in first k elements
        int low_p =0, high_p =k;
        while(low_p < high_p){
            int mid = (low_p + high_p) /2;
            if(sorted_customers[mid].v >= r_j){
                low_p = mid +1;
            }
            else{
                high_p = mid;
            }
        }
        int p = low_p;
        if(p ==0){
            printf("0\n");
        }
        else{
            printf("%lld\n", max_dp[p-1]);
        }
    }
    free(customers1);
    free(sorted_customers);
    free(max_dp);
    return 0;
}