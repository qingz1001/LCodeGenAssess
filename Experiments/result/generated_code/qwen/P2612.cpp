#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 100
#define MAXK 30

double factorial[MAXN];

void precompute_factorials() {
    factorial[0] = 1.0;
    for (int i = 1; i < MAXN; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
}

int calculate_permutations(int n) {
    return factorial[n];
}

int calculate_variations(int n, int m) {
    if (m == 0) return 1;
    if (n == 1) return 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += calculate_variations(n - 1, m - abs(i - n));
    }
    return sum;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    precompute_factorials();

    int total_permutations = calculate_permutations(n);
    int valid_permutations = calculate_variations(n, m);

    double probability = (double)valid_permutations / total_permutations;

    printf("%.3f\n", probability);

    return 0;
}