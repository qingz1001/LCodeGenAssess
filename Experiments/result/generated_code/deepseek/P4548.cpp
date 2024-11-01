#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 10000

typedef struct {
    int length;
    int *name;
} Chief;

int *compute_prefix_function(int *pattern, int m) {
    int *pi = (int *)malloc(sizeof(int) * (m + 1));
    pi[0] = -1;
    int k = -1;
    for (int i = 1; i <= m; i++) {
        while (k >= 0 && pattern[k] != pattern[i - 1]) {
            k = pi[k];
        }
        pi[i] = ++k;
    }
    return pi;
}

int expected_time(int n, Chief *chief) {
    int m = chief->length;
    int *name = chief->name;
    int *pi = compute_prefix_function(name, m);
    int *f = (int *)calloc(m + 1, sizeof(int));
    int *g = (int *)calloc(m + 1, sizeof(int));

    for (int i = m - 1; i >= 0; i--) {
        f[i] = (f[i + 1] * n + 1) % MOD;
        g[i] = (g[i + 1] * n + f[i + 1]) % MOD;
        if (pi[i + 1] != -1) {
            f[i] = (f[i] - f[pi[i + 1]] + MOD) % MOD;
            g[i] = (g[i] - g[pi[i + 1]] + MOD) % MOD;
        }
    }

    int result = (g[0] + 1) % MOD;
    free(pi);
    free(f);
    free(g);
    return result;
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    Chief *chiefs = (Chief *)malloc(sizeof(Chief) * t);

    for (int i = 0; i < t; i++) {
        int m;
        scanf("%d", &m);
        chiefs[i].length = m;
        chiefs[i].name = (int *)malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &chiefs[i].name[j]);
        }
    }

    for (int i = 0; i < t; i++) {
        int result = expected_time(n, &chiefs[i]);
        printf("%04d\n", result);
        free(chiefs[i].name);
    }

    free(chiefs);
    return 0;
}