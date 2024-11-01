#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    long long total_length = 0;
    for (int i = 0; i < n; i++) {
        long long length;
        scanf("%lld", &length);
        total_length += length;
    }

    long long left = 0, right = total_length / k, max_length = 0;
    while (left <= right) {
        long long mid = (left + right) / 2;
        if (mid == 0) break;

        long long pieces = 0;
        for (int i = 0; i < n; i++) {
            pieces += (total_length / mid);
        }

        if (pieces >= k) {
            max_length = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%lld\n", max_length);
    return 0;
}