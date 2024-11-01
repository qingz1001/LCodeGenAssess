#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

typedef struct {
    ll T;
    ll A;
    ll B;
    ll C;
    ll S;
    ll E;
} Customer;

int cmp(const void *a, const void *b){
    Customer *c1 = (Customer*)a;
    Customer *c2 = (Customer*)b;
    if(c1->E != c2->E)
        return (c1->E < c2->E) ? -1 : 1;
    return 0;
}

int main(){
    ll N, Q;
    scanf("%lld %lld", &N, &Q);
    Customer customers[N];
    for(ll i = 0; i < N; i++){
        scanf("%lld %lld %lld %lld", &customers[i].T, &customers[i].A, &customers[i].B, &customers[i].C);
        customers[i].S = customers[i].T;
        ll distance = llabs(customers[i].B - customers[i].A);
        customers[i].E = customers[i].T + distance;
    }
    qsort(customers, N, sizeof(Customer), cmp);
    // Precompute dp
    ll dp[N];
    for(ll i = 0; i < N; i++) dp[i] = customers[i].C * llabs(customers[i].B - customers[i].A);
    for(ll i = 0; i < N; i++){
        for(ll j = 0; j < i; j++){
            ll move_time = llabs(customers[i].A - customers[j].B);
            if(customers[j].E + move_time <= customers[i].S){
                if(dp[i] < dp[j] + customers[i].C * llabs(customers[i].B - customers[i].A))
                    dp[i] = dp[j] + customers[i].C * llabs(customers[i].B - customers[i].A);
            }
        }
    }
    // Compute prefix max
    ll prefix_max[N];
    prefix_max[0] = dp[0];
    for(ll i = 1; i < N; i++) {
        if(prefix_max[i-1] > dp[i]) prefix_max[i] = prefix_max[i-1];
        else prefix_max[i] = dp[i];
    }
    // Process queries
    for(ll q = 0; q < Q; q++){
        ll P, X;
        scanf("%lld %lld", &P, &X);
        ll max_wage = 0;
        for(ll i = 0; i < N; i++){
            // Check if can reach customer i from (P, X)
            ll start_time = customers[i].S;
            ll end_time = customers[i].E;
            ll distance_to_start = llabs(customers[i].A - X);
            if(P > end_time) continue;
            ll earliest_start = (P > customers[i].T) ? P : customers[i].T;
            ll required_time = llabs(customers[i].A - X);
            if(earliest_start + required_time > end_time) continue;
            if(max_wage < dp[i]){
                max_wage = dp[i];
            }
        }
        printf("%lld\n", max_wage);
    }
    return 0;
}