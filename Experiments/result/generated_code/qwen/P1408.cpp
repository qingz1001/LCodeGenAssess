#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long min_cost = 0;

    for (int i = 0; i < n - 1; i++) {
        int current_gcd = arr[i];
        for (int j = i + 1; j < n && current_gcd != 1; j++) {
            current_gcd = gcd(current_gcd, arr[j]);
        }
        if (current_gcd != 1) {
            min_cost += current_gcd;
            for (int j = i; j < n; j++) {
                arr[j] /= current_gcd;
            }
        }
    }

    printf("%lld\n", min_cost);

    free(arr);
    return 0;
}