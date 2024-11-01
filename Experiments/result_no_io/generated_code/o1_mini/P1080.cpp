#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long a;
    long long b;
} Minister;

int compare(const void *a, const void *b) {
    Minister *m1 = (Minister *)a;
    Minister *m2 = (Minister *)b;
    if (m1->b != m2->b)
        return (m2->b > m1->b) - (m2->b < m1->b);
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    long long king_a, king_b;
    scanf("%lld %lld", &king_a, &king_b);
    Minister ministers[n];
    for(int i=0;i<n;i++) {
        scanf("%lld %lld", &ministers[i].a, &ministers[i].b);
    }
    // Binary search
    long long left = 1;
    long long right = 1000000000000000000LL;
    while(left < right){
        long long mid = left + (right - left) / 2;
        // Sort ministers in decreasing order of b
        qsort(ministers, n, sizeof(Minister), compare);
        // Check condition
        double log_prod = log((double)king_a);
        int ok = 1;
        for(int i=0;i<n;i++){
            double limit = log((double)mid) + log((double)ministers[i].b) - log((double)king_a);
            if(log_prod > limit + 1e-12){
                ok = 0;
                break;
            }
            log_prod += log((double)ministers[i].a);
        }
        if(ok){
            right = mid;
        }
        else{
            left = mid + 1;
        }
    }
    printf("%lld\n", left);
}