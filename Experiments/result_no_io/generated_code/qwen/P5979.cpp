#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n;
    scanf("%d", &n);
    
    int *c = (int *)malloc(n * sizeof(int));
    int *d = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &c[i], &d[i]);
    }
    
    long long max_groups = 0;
    long long ways = 1;
    int start = 0;
    
    for (int end = 0; end < n; end++) {
        while (end + 1 < n && d[end] >= c[end + 1]) {
            end++;
        }
        
        if (end - start + 1 > max_groups) {
            max_groups = end - start + 1;
            ways = 1;
        } else if (end - start + 1 == max_groups) {
            ways = (ways * (end - start + 1)) % MOD;
        }
        
        start = end + 1;
    }
    
    if (max_groups == 0) {
        printf("NIE\n");
    } else {
        printf("%lld %lld\n", max_groups, ways);
    }
    
    free(c);
    free(d);
    
    return 0;
}