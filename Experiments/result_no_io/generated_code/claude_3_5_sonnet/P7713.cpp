#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int n, m;
int a[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), cmp);

    long long sum = 0;
    for (int i = 1; i < n - 1; i++) {
        sum += a[i];
    }

    int left = 1, right = n - 2;
    while (m > 0 && left <= right) {
        if (a[n-1] - a[right] <= a[left] - a[0]) {
            int diff = a[n-1] - a[right];
            int count = (diff < m) ? diff : m;
            sum += count;
            a[right] += count;
            m -= count;
            right--;
        } else {
            int diff = a[left] - a[0];
            int count = (diff < m) ? diff : m;
            sum += count;
            a[left] += count;
            m -= count;
            left++;
        }
    }

    printf("%lld\n", sum);
    return 0;
}