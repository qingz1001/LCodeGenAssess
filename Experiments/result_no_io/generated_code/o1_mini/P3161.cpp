#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int t;
    int g;
    int m;
} Order;

int compare_orders(const void *a, const void *b) {
    Order *oa = (Order *)a;
    Order *ob = (Order *)b;
    if (oa->t != ob->t)
        return oa->t - ob->t;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Order orders[10];
    for(int i=0;i<n;i++) {
        scanf("%d %d %d", &orders[i].t, &orders[i].g, &orders[i].m);
    }
    int max_income = 0;
    int total_subsets = 1 << n;
    for(int mask=1; mask < total_subsets; mask++){
        // Extract orders in subset
        Order subset[10];
        int cnt=0;
        for(int i=0;i<n;i++) if(mask & (1<<i)) subset[cnt++] = orders[i];
        // Sort subset by time
        qsort(subset, cnt, sizeof(Order), compare_orders);
        // Simulate
        int p=1;
        long long goods=0;
        int current_time=0;
        int income=0;
        int feasible = 1;
        for(int i=0;i<cnt;i++){
            int ti = subset[i].t;
            int gi = subset[i].g;
            int mi = subset[i].m;
            int delta_t = ti - current_time;
            if(delta_t <0){
                feasible =0;
                break;
            }
            if(gi <= goods){
                goods -= gi;
                income += mi;
                current_time = ti;
                continue;
            }
            long long target = gi - goods;
            // Calculate D = (delta_t + p)^2 -4*target
            double D_val = ((double)(delta_t) + (double)(p)) * ((double)(delta_t) + (double)(p)) - 4.0 * ((double)target);
            if(D_val < -1e-6){
                feasible =0;
                break;
            }
            if(D_val <0) D_val =0;
            double sqrt_D = sqrt(D_val);
            double r = ((double)(delta_t) - (double)(p) + sqrt_D) / 2.0;
            int k_max = (int)(floor(r + 1e-9));
            if(k_max > delta_t) k_max = delta_t;
            if(k_max <0) k_max =0;
            // Find the maximum k <=k_max that satisfies
            while(k_max >=0){
                int p_new = p + k_max;
                long long goods_new = goods + (long long)(delta_t - k_max) * (long long)(p_new);
                if(goods_new >= gi){
                    p = p_new;
                    goods = goods_new - (long long)(gi);
                    income += mi;
                    current_time = ti;
                    break;
                }
                k_max--;
            }
            if(k_max <0){
                feasible =0;
                break;
            }
        }
        if(feasible && income > max_income){
            max_income = income;
        }
    }
    printf("%d\n", max_income);
    return 0;
}