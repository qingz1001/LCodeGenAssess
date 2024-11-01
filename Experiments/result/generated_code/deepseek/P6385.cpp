#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 30005

char S[MAXN];
int n, q;

int min(int a, int b) {
    return a < b ? a : b;
}

int find_j(int i, int p) {
    int len = n - p;
    for (int j = i; j <= n; ++j) {
        if (strncmp(S + i - 1, S + p - 1, j - i + 1) == 0) {
            return j;
        }
    }
    return -1; // This should never happen due to problem constraints
}

int solve(int i, int p, int k) {
    int j = find_j(i, p);
    int cost = n - j;

    // Move i to k
    if (i < k) {
        cost += k - i;
    } else if (i > k) {
        cost += i - k;
    }

    return cost;
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", S);

    for (int t = 0; t < q; ++t) {
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);
        printf("%d\n", solve(i, p, k));
    }

    return 0;
}