#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int P, n, m;
    scanf("%d %d", &P, &n, &m);
    
    if (n == 0) {
        printf("Impossible\n");
        return 0;
    }
    
    long long result = 1;
    for (int i = 0; i < m; ++i) {
        int w;
        scanf("%d", &w);
        if (w > n) {
            printf("Impossible\n");
            return 0;
        }
        result = result * (n - w + 1) % P;
        n -= w;
    }
    
    printf("%lld\n", result);
    return 0;
}