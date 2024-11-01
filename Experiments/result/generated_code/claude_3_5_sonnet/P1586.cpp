#include <stdio.h>
#include <math.h>

int count_solutions(int n) {
    int count = 0;
    int limit = sqrt(n);

    for (int a = 0; a <= limit; a++) {
        for (int b = a; b <= limit; b++) {
            for (int c = b; c <= limit; c++) {
                int d_squared = n - a*a - b*b - c*c;
                if (d_squared < 0) break;
                int d = sqrt(d_squared);
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
        printf("%d\n", count_solutions(n));
    }

    return 0;
}