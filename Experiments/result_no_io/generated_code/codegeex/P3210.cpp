#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    ll alice = 0, bob = 0;
    int left = -1, right = n;

    // Find the first non-zero stone pile
    while (left + 1 < right && a[++left] == 0);
    // Find the last non-zero stone pile
    while (left + 1 < right && a[--right] == 0);

    // Calculate the optimal strategy
    while (left < right) {
        if (a[left] >= a[right]) {
            alice += a[left];
            left++;
            while (left + 1 < right && a[left] == 0) left++;
        } else {
            alice += a[right];
            right--;
            while (left + 1 < right && a[right] == 0) right--;
        }
    }

    bob = sum - alice;

    printf("%lld %lld\n", alice, bob);

    free(a);
    return 0;
}