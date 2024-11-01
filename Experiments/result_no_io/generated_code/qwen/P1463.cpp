#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000000000

int prime[MAX_N + 1];
int g[MAX_N + 1];

void sieve() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!prime[i]) {
            for (int j = i; j <= MAX_N; j += i) {
                prime[j] = 1;
                g[j]++;
            }
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    sieve();

    int max_g = 0;
    int largest_antiprime = 0;

    for (int i = 1; i <= N; i++) {
        if (g[i] > max_g) {
            max_g = g[i];
            largest_antiprime = i;
        }
    }

    printf("%d\n", largest_antiprime);

    return 0;
}