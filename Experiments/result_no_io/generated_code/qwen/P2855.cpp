#include <stdio.h>
#include <stdlib.h>

#define MAX_L 1000000000
#define MAX_N 50000

int stones[MAX_N + 2];
int n, m;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int binary_search(int l, int r) {
    while (l < r) {
        int mid = (l + r + 1) / 2;
        int count = 0, prev = 0;
        for (int i = 1; i <= n + 1; i++) {
            if (stones[i] - stones[prev] >= mid) {
                prev = i;
            } else {
                count++;
            }
        }
        if (count > m) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    return l;
}

int main() {
    int l;
    scanf("%d %d %d", &l, &n, &m);
    stones[0] = 0;
    stones[n + 1] = l;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &stones[i]);
    }

    qsort(stones, n + 2, sizeof(int), compare);

    printf("%d\n", binary_search(1, l));

    return 0;
}