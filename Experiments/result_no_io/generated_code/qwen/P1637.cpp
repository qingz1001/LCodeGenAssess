#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i]) {
                for (int k = j + 1; k < n; k++) {
                    if (a[k] > a[j]) {
                        count++;
                    }
                }
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}