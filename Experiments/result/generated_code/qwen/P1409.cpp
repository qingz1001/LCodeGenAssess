#include <stdio.h>
#include <stdlib.h>

double probability(int n, int m) {
    if (n == 1) return 1.0;
    double p = 0.0;
    for (int i = 1; i <= 6; i++) {
        if (i == 1) p += 1.0 / 6 * 1.0;
        else if (i == 2 || i == 4 || i == 6) p += 1.0 / 6 * probability(n - 1, m);
        else if (i == 3 || i == 5) p += 1.0 / 6 * probability(n - 1, (m + n - 2) % (n - 1) + 1);
    }
    return p;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%.9f\n", probability(n, m));
    return 0;
}