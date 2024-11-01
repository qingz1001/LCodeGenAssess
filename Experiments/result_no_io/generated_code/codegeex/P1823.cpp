#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    long long heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &heights[i]);
    }

    long long visible_pairs = 0;
    int current_tallest = 0;

    for (int i = 0; i < n; i++) {
        if (heights[i] > current_tallest) {
            visible_pairs += current_tallest;
            current_tallest = heights[i];
        } else {
            visible_pairs += current_tallest - heights[i];
        }
    }

    printf("%lld\n", visible_pairs);
    return 0;
}