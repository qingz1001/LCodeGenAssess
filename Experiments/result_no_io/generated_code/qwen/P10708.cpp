#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, x, y;
    scanf("%d %d %d", &N, &x, &y);
    
    int *a = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    
    long long min_cost = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] * x <= y) {
            min_cost += a[i] * x;
        } else {
            min_cost += y;
        }
    }
    
    printf("%lld\n", min_cost);
    
    free(a);
    return 0;
}