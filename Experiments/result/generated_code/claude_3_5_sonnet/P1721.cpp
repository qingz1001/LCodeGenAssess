#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 8000
#define MAX_P 3000

typedef long double ld;

int n, k, p;
int h[MAX_N];
ld dp[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

ld solve() {
    qsort(h, n, sizeof(int), cmp);
    
    for (int i = 0; i < n; i++) {
        dp[i] = h[i];
        ld sum = h[i];
        for (int j = i - 1; j >= 0 && i - j <= k; j--) {
            sum += h[j];
            ld avg = sum / (i - j + 1);
            if (avg > dp[i]) dp[i] = avg;
        }
    }
    
    return dp[0];
}

int main() {
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }
    
    ld result = solve();
    printf("%.*Lf\n", p, result);
    
    return 0;
}