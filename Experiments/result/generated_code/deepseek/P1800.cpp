#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100
#define MAX_M 100

int n, m;
int d1[MAX_N], d2[MAX_N];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int min_days() {
    int left = 0, right = INT_MAX;
    while (left < right) {
        int mid = (left + right) / 2;
        long long total_first = 0, total_second = 0;
        for (int i = 0; i < n; i++) {
            if (d1[i] <= mid) {
                total_first += (mid / d1[i]);
            }
            if (d2[i] <= mid) {
                total_second += (mid / d2[i]);
            }
        }
        if (total_first >= m && total_second >= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &d1[i], &d2[i]);
    }
    printf("%d\n", min_days());
    return 0;
}