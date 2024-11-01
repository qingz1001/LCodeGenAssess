#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

long long woods[MAX_N];
int n, k;

int check(long long length) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        count += woods[i] / length;
    }
    return count >= k;
}

long long binary_search() {
    long long left = 1, right = 1e8, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (check(mid)) {
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