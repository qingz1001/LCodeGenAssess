#include <stdio.h>
#include <limits.h>

#define MAX_LEN 100000

int main() {
    long long l, k;
    scanf("%lld %lld", &l, &k);
    
    long long logs[MAX_LEN];
    for (long long i = 0; i < l; i++) {
        scanf("%lld", &logs[i]);
    }
    
    long long min_n = LLONG_MAX;
    long long max_n = LLONG_MIN;
    
    long long current_code = 0;
    long long solved_count = 0;
    
    for (long long i = 0; i < l; i++) {
        current_code += logs[i];
        
        if (current_code >= 0) {
            if (current_code >= k) {
                min_n = (min_n < current_code - k + 1) ? min_n : current_code - k + 1;
            }
            if (current_code >= k - 1) {
                max_n = (max_n > current_code - k + 1) ? max_n : current_code - k + 1;
            }
            
            if (current_code >= k) {
                solved_count++;
                current_code = 0;
            }
        }
    }
    
    if (solved_count < k) {
        printf("-1\n");
    } else {
        printf("%lld %lld\n", min_n, max_n);
    }
    
    return 0;
}