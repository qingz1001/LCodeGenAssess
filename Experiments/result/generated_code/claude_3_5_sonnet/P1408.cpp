#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    int arr[MAX_N];
    long long cost = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        int g = gcd(arr[i], arr[i+1]);
        while (g > 1) {
            cost += g;
            arr[i] /= g;
            arr[i+1] /= g;
            g = gcd(arr[i], arr[i+1]);
        }
    }

    printf("%lld\n", cost);

    return 0;
}