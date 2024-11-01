#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    int *max_gcd = (int *)calloc(n, sizeof(int));
    int max_val = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        max_val = (a[i] > max_val) ? a[i] : max_val;
    }

    int *count = (int *)calloc(max_val + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }

    int current_gcd = 0;
    for (int i = max_val; i >= 1; i--) {
        if (count[i] > 0) {
            current_gcd = i;
            break;
        }
    }

    for (int i = max_val; i >= 1; i--) {
        if (count[i] > 0) {
            for (int j = max_val; j >= i; j--) {
                if (count[j] > 0) {
                    current_gcd = gcd(current_gcd, j);
                    for (int k = j; k <= max_val; k += j) {
                        count[k] = count[j];
                    }
                }
            }
            max_gcd[count[i] - 1] = current_gcd;
            for (int j = i; j <= max_val; j += i) {
                count[j] = count[i];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", max_gcd[i]);
    }

    free(a);
    free(max_gcd);
    free(count);

    return 0;
}