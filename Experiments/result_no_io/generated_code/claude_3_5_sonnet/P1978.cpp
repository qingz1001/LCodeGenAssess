#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005

long long a[MAX_N];
int used[MAX_N];

int cmp(const void *a, const void *b) {
    long long va = *(long long*)a;
    long long vb = *(long long*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    qsort(a, n, sizeof(long long), cmp);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            ans++;
            used[i] = 1;
            long long target = a[i] * k;
            int pos = i + 1;
            while (pos < n && a[pos] <= target) {
                if (a[pos] == target) {
                    used[pos] = 1;
                    target *= k;
                }
                pos++;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}