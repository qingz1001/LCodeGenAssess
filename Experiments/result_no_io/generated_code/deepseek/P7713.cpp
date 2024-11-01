#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int left = 0, right = n - 1;
    while (m > 0 && left < right) {
        if (left < right - 1 && a[left + 1] - a[left] <= a[right] - a[right - 1]) {
            int diff = a[left + 1] - a[left];
            if (m >= (left + 1) * diff) {
                m -= (left + 1) * diff;
                a[left] += diff;
            } else {
                a[left] += m / (left + 1);
                break;
            }
        } else {
            int diff = a[right] - a[right - 1];
            if (m >= (n - right) * diff) {
                m -= (n - right) * diff;
                a[right] -= diff;
            } else {
                a[right] -= m / (n - right);
                break;
            }
        }
        while (left < n - 1 && a[left] == a[left + 1]) left++;
        while (right > 0 && a[right] == a[right - 1]) right--;
    }

    long long sum = 0;
    for (int i = 1; i < n - 1; i++) {
        sum += a[i];
    }

    printf("%lld\n", sum * (n - 2));

    free(a);
    return 0;
}