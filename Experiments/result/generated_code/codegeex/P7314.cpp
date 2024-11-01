#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int min_diff = INT_MAX;
    for (int i = 0; i < n - 1; i++) {
        int max_val = a[i];
        int min_val = a[i];
        for (int j = i + 1; j < n; j++) {
            if (a[j] > max_val) {
                max_val = a[j];
            }
            if (a[j] < min_val) {
                min_val = a[j];
            }
            int diff = max_val - min_val;
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }

    printf("%d\n", min_diff);
    return 0;
}