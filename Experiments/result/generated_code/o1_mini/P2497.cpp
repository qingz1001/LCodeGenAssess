#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef long long ll;

typedef struct {
    ll s;
    double dp;
} Pair;

int cmp(const void *a, const void *b) {
    Pair *pa = (Pair*)a;
    Pair *pb = (Pair*)b;
    if (pa->s < pb->s) return -1;
    if (pa->s > pb->s) return 1;
    return 0;
}

int main(){
    int n;
    ll m;
    scanf("%d %lld", &n, &m);
    ll *x = (ll*)malloc(n * sizeof(ll));
    int *r = (int*)malloc(n * sizeof(int));
    int *v = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) {
        scanf("%lld %d %d", &x[i], &r[i], &v[i]);
    }
    double *dp = (double*)malloc(n * sizeof(double));
    // Initialize sorted list
    Pair *sorted = (Pair*)malloc(n * sizeof(Pair));
    int sorted_size = 0;
    // Initialize dp
    dp[0] = (double)v[0];
    // Insert first
    sorted[sorted_size].s = x[0] + r[0];
    sorted[sorted_size].dp = dp[0];
    sorted_size++;
    for(int i=1;i<n;i++){
        ll xi = x[i];
        double min_cost = 1e18;
        if(sorted_size >0){
            // Binary search for the largest s <= xi
            int left =0, right = sorted_size -1, pos = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(sorted[mid].s <= xi){
                    pos = mid;
                    left = mid +1;
                }
                else{
                    right = mid -1;
                }
            }
            if(pos != -1){
                double cost = sorted[pos].dp + sqrt((double)(xi - sorted[pos].s));
                min_cost = cost;
            }
        }
        if(i ==0){
            dp[i] = (double)v[i];
        }
        else{
            if(min_cost <1e18){
                dp[i] = (double)v[i] + min_cost;
            }
            else{
                dp[i] = 1e18;
            }
        }
        // Insert x[i] + r[i] and dp[i] into sorted array
        if(dp[i] <1e18){
            Pair new_pair;
            new_pair.s = x[i] + r[i];
            new_pair.dp = dp[i];
            // Insert while keeping sorted
            if(sorted_size ==0){
                sorted[sorted_size++] = new_pair;
            }
            else{
                // Find the position to insert
                int pos_insert = sorted_size;
                while(pos_insert >0 && sorted[pos_insert -1].s > new_pair.s){
                    sorted[pos_insert] = sorted[pos_insert -1];
                    pos_insert--;
                }
                sorted[pos_insert] = new_pair;
                sorted_size++;
            }
        }
    }
    // Find the minimal dp[i] where x[i] + r[i] >=m
    double answer =1e18;
    for(int i=0;i<n;i++){
        if(x[i] + r[i] >=m){
            if(dp[i] <answer){
                answer = dp[i];
            }
        }
    }
    printf("%.3lf\n", answer);
    free(x);
    free(r);
    free(v);
    free(dp);
    free(sorted);
    return 0;
}