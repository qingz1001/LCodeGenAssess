#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_M 50000

int stones[MAX_N + 2];
int n, m;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int max_min_jump(int l, int r, int m) {
    if (m == 0 || l >= r) return stones[r] - stones[l];
    int mid = (l + r) / 2;
    int left = max_min_jump(l, mid, m - 1);
    int right = max_min_jump(mid, r, m - 1);
    return left > right ? left : right;
}

int main() {
    int l, m;
    scanf("%d %d %d", &l, &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &stones[i]);
    }
    stones[0] = 0;
    stones[n + 1] = l;
    qsort(stones, n + 2, sizeof(int), compare);
    printf("%d\n", max_min_jump(0, n + 1, m));
    return 0;
}