#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int n, m;
    int a[MAX_N];
    
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    qsort(a, n, sizeof(int), cmp);
    
    long long sum = 0;
    for (int i = 1; i < n - 1; i++) {
        sum += a[i];
    }
    
    int operations = m;
    for (int i = n - 2; i >= 1 && operations > 0; i--) {
        int diff = a[n-1] - a[i];
        if (diff == 0) break;
        
        int increment = (diff < operations) ? diff : operations;
        sum += increment;
        operations -= increment;
    }
    
    printf("%lld\n", sum);
    
    return 0;
}