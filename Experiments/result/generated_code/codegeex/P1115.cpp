#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int max_sum = a[0];
    int current_sum = a[0];

    for (int i = 1; i < n; i++) {
        current_sum = (current_sum > 0) ? current_sum + a[i] : a[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    printf("%d\n", max_sum);
    return 0;
}