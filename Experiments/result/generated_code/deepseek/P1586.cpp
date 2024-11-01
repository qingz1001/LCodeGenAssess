#include <stdio.h>
#include <math.h>

int count_ways(int n) {
    int count = 0;
    for (int a = 0; a * a <= n; a++) {
        for (int b = a; a * a + b * b <= n; b++) {
            for (int c = b; a * a + b * b + c * c <= n; c++) {
                for (int d = c; a * a + b * b + c * c + d * d <= n; d++) {
                    if (a * a + b * b + c * c + d * d == n) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", count_ways(n));
    }
    return 0;
}