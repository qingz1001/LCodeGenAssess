#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int heights[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &heights[i]);
    }

    long long count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (abs(heights[i] - heights[j]) <= abs(i - j)) {
                ++count;
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}