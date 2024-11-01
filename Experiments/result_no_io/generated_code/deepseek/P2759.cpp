#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int x = 1;
    while (1) {
        long long power = (long long)x * log10(x);
        if (power + 1 >= n) {
            printf("%d\n", x);
            break;
        }
        x++;
    }

    return 0;
}