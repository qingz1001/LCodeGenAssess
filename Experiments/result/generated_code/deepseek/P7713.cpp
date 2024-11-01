#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int left = 0, right = n - 1;
    while (m > 0 && left < right) {
        if (left + 1 < right && a[left + 1] - a[left] <= a[right] - a[right - 1]) {
            int diff = a[left + 1] - a[left];
            if (m >= (left + 1) * diff) {
                m -= (left + 1) * diff;
                for (int i = 0; i <= left; i++) {
                    a[i] += diff;
                }
            } else {
                int inc = m / (left + 1);
                for (int i = 0; i <= left; i++) {
                    a[i] += inc;
                }
                m = 0;
            }
        } else {
            int diff = a[right] - a[right - 1];
            if (m >= (n - right) * diff) {
                m -= (n - right) * diff;
                for (int i = right; i < n; i++) {
                    a[i] -= diff;
                }
            } else {
                int dec = m / (n - right);
                for (int i = right; i < n; i++) {
                    a[i] -= dec;
                }
                m = 0;
            }
        }
        qsort(a, n, sizeof(int), compare);
    }

    long long sum = 0;
    for (int i = 1; i < n - 1; i++) {
        sum += a[i];
    }

    printf("%lld\n", sum * (n - 2));
    return 0;
}