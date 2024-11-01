#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int x = 1;
    while (1) {
        double log10_x = log10(x);
        double log10_xx = x * log10_x;
        if (log10_xx >= n - 1) {
            printf("%d\n", x);
            break;
        }
        x++;
    }

    return 0;
}