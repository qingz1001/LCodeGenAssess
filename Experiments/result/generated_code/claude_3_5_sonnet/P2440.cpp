#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

long long woods[MAX_N];
int n, k;

int can_cut(long long length) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += woods[i] / length;
        if (count >= k) return 1;
    }
    return 0;
}

long long binary_search() {
    long long left = 1, right = 1000000000, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (can_cut(mid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &woods[i]);
    }

    long long result = binary_search();
    printf("%lld\n", result);

    return 0;
}