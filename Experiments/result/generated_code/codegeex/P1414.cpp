#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXV 1000001

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);
    int a[MAXN], freq[MAXV] = {0}, maxv = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        freq[a[i]]++;
        if (a[i] > maxv) {
            maxv = a[i];
        }
    }

    for (int i = maxv; i >= 1; i--) {
        for (int j = 2 * i; j <= maxv; j += i) {
            freq[i] += freq[j];
        }
    }

    for (int k = 1; k <= n; k++) {
        int max_gcd = 1;
        for (int i = 1; i <= maxv; i++) {
            if (freq[i] >= k) {
                max_gcd = i;
                break;
            }
        }
        printf("%d\n", max_gcd);
    }

    return 0;
}