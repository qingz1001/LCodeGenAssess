#include <stdio.h>
#include <limits.h>

int main() {
    int l, k;
    scanf("%d %d", &l, &k);
    
    long long sum = 0;
    int max_code = INT_MIN;
    int min_code = INT_MAX;
    
    for (int i = 0; i < l; i++) {
        int x;
        scanf("%d", &x);
        sum += x;
        
        if (sum >= 0) {
            max_code = (max_code > sum ? max_code : sum);
        }
        
        if (sum < 0) {
            min_code = (min_code < sum ? min_code : sum);
        }
    }
    
    if (k == 0 && sum <= 0) {
        printf("-1\n");
        return 0;
    }
    
    if (k == 0 && sum > 0) {
        printf("0 %lld\n", sum);
        return 0;
    }
    
    if (k != 0 && sum <= 0) {
        printf("%d %d\n", min_code, -1);
        return 0;
    }
    
    if (k != 0 && sum > 0) {
        printf("%d %lld\n", min_code, max_code);
        return 0;
    }
    
    return 0;
}