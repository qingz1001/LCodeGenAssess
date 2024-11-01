#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int max_sum = INT_MIN, current_sum = 0;
    for (int i = 0; i < n; i++) {
        current_sum += a[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        if (current_sum < 0) {
            current_sum = 0;
        }
    }

    printf("%d\n", max_sum);
    return 0;
}