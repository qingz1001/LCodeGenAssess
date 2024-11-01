#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001
#define MAXM 1000000001

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    long long weights[MAXM];
    for (int i = 0; i < m; ++i) {
        scanf("%lld", &weights[i]);
    }
    
    long long containers[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &containers[i]);
    }
    
    // Sort weights and containers
    qsort(weights, m, sizeof(long long), (void*)cmp);
    qsort(containers, n, sizeof(long long), (void*)cmp);
    
    int count = 0;
    int i = 0, j = 0;
    
    while (i < m && j < n) {
        if (weights[i] <= containers[j]) {
            ++count;
            ++i;
        } else {
            ++j;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}

// Comparator function for qsort
int cmp(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}