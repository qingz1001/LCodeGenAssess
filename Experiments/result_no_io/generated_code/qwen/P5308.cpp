#include <stdio.h>
#include <math.h>

int main() {
    int n, k;
    double bonus = 0.0;

    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; i++) {
        if (i == k - 1) {
            bonus += (double)n / (n + 1);
        } else {
            bonus += (double)n / (n + 1);
            n--;
        }
    }

    printf("%.9f\n", bonus);

    return 0;
}