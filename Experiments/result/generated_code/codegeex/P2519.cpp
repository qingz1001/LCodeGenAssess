#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n], b[n], c[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        c[i] = a[i] + b[i] + 1;
    }
    
    qsort(a, n, sizeof(int), cmp);
    qsort(b, n, sizeof(int), cmp);
    qsort(c, n, sizeof(int), cmp);
    
    int high = 0, low = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        while (high < n && a[high] < c[i]) high++;
        while (low < n && b[low] < c[i]) low++;
        ans += (high - i) + (i - low);
    }
    
    printf("%d\n", ans);
    return 0;
}