#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    long long n, m, p, q;
    scanf("%lld %lld %lld %lld", &n, &m, &p, &q);
    
    // Read dishes
    long long *d = (long long*)malloc(m * sizeof(long long));
    long long *price = (long long*)malloc(m * sizeof(long long));
    for(long long i=0;i<m;i++) {
        scanf("%lld %lld", &d[i], &price[i]);
    }
    
    // Read p thresholds
    long long min_p = LLONG_MAX;
    if(p >0){
        for(long long i=0;i<p;i++){
            long long tp;
            scanf("%lld", &tp);
            if(tp < min_p){
                min_p = tp;
            }
        }
    } else {
        min_p = LLONG_MAX;
    }
    
    // Read q thresholds
    long long max_q = LLONG_MIN;
    if(q >0){
        for(long long i=0;i<q;i++){
            long long tq;
            scanf("%lld", &tq);
            if(tq > max_q){
                max_q = tq;
            }
        }
    } else {
        max_q = LLONG_MIN;
    }
    
    if(n > p + q){
        // Calculate ceil(m /n)
        long long ans = (m + n -1) /n;
        printf("%lld\n", ans);
    }
    else{
        // Check if all dishes can be assigned to p or q
        int possible = 1;
        for(long long i=0;i<m;i++){
            if(d[i] < min_p && price[i] > max_q){
                possible = 0;
                break;
            }
        }
        if(!possible){
            printf("-1\n");
        }
        else{
            // Calculate ceil(m / (p + q))
            long long total = p + q;
            if(total ==0){
                // No one to assign dishes
                printf("-1\n");
                return 0;
            }
            long long ans = (m + total -1)/total;
            printf("%lld\n", ans);
        }
    }
    
    free(d);
    free(price);
    return 0;
}