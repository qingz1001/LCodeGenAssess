#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    // Initialize adjacency list for dislikes
    int *dislikes = (int *)calloc(n + 1, sizeof(int));
    for (int i = 0; i < k; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        dislikes[a]++;
        dislikes[b]++;
    }

    // Calculate the number of valid seating arrangements
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        if (dislikes[i] == 0) {
            result = (result * 2) % MOD;
        }
    }

    printf("%lld\n", result);

    free(dislikes);
    return 0;
}