#include <stdio.h>
#include <limits.h>

typedef long long ll;

int main(){
    int n;
    ll m;
    scanf("%d %lld", &n, &m);
    
    ll a;
    ll sum = 0;
    ll min_val = LLONG_MAX;
    ll max_val = LLONG_MIN;
    int count_min = 0, count_max = 0;
    
    for(int i=0;i<n;i++){
        scanf("%lld", &a);
        sum += a;
        if(a < min_val){
            min_val = a;
            count_min = 1;
        }
        else if(a == min_val){
            count_min++;
        }
        if(a > max_val){
            max_val = a;
            count_max = 1;
        }
        else if(a == max_val){
            count_max++;
        }
    }
    
    ll count_non_max_min = n - count_min - count_max;
    ll sum_non_max_min = sum - ((ll)count_min * min_val) - ((ll)count_max * max_val);
    ll total_possible_ops = 0;
    if(count_non_max_min >0){
        total_possible_ops = ((ll)count_non_max_min * max_val) - sum_non_max_min;
    }
    
    ll increment = m < total_possible_ops ? m : total_possible_ops;
    ll final_sum_minus_max_min = (sum - max_val - min_val) + increment;
    
    printf("%lld\n", final_sum_minus_max_min);
    return 0;
}