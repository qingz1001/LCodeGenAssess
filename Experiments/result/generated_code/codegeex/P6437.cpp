#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int max_sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int sum = a[i] + a[j] + a[k];
                if (sum <= m && sum > max_sum) {
                    max_sum = sum;
                }
            }
        }
    }

    printf("%d\n", max_sum);
    return 0;
}