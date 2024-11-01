#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long count = 0;
    for (int i = 1; i < n - 1; i++) {
        int smaller_left = 0, larger_right = 0;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                smaller_left++;
            }
        }
        for (int k = i + 1; k < n; k++) {
            if (a[k] > a[i]) {
                larger_right++;
            }
        }
        count += (long long)smaller_left * larger_right;
    }

    printf("%lld\n", count);

    return 0;
}