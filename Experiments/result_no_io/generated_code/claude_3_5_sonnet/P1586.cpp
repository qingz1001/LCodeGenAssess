#include <stdio.h>
#include <math.h>

int count_decompositions(int n) {
    int count = 0;
    int sqrt_n = (int)sqrt(n);

    for (int a = 0; a <= sqrt_n; a++) {
        for (int b = a; b <= sqrt_n; b++) {
            for (int c = b; c <= sqrt_n; c++) {
                int d_squared = n - a*a - b*b - c*c;
                if (d_squared < 0) break;
                int d = (int)sqrt(d_squared);
                if (d*d == d_squared) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    int t, n;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        printf("%d\n", count_decompositions(n));
    }

    return 0;
}