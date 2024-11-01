#include <stdio.h>
#include <stdlib.h>

int cmp_ll(const void *a, const void *b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x < y) return -1;
    else if (x > y) return 1;
    else return 0;
}

int upper_bound_func(long long arr[], int n, long long key) {
    int l = 0, r = n;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (arr[m] <= key)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

int lower_bound_func(long long arr[], int n, long long key) {
    int l = 0, r = n;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (arr[m] < key)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long *start = (long long*) malloc(n * sizeof(long long));
    long long *end = (long long*) malloc(n * sizeof(long long));
    for(int i = 0; i < n; i++) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        start[i] = a;
        end[i] = a + b;
    }
    qsort(start, n, sizeof(long long), cmp_ll);
    qsort(end, n, sizeof(long long), cmp_ll);
    for(int i = 0; i < m; i++) {
        long long x, y;
        scanf("%lld %lld", &x, &y);
        long long q_start = x;
        long long q_end = x + y;
        int cnt1 = upper_bound_func(start, n, q_end);
        int cnt2 = lower_bound_func(end, n, q_start + 1);
        printf("%d\n", cnt1 - cnt2);
    }
    free(start);
    free(end);
    return 0;
}