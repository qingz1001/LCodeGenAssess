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
    int len = 0;
    while (i + len < n && p + len < n && S[i + len] == S[p + len]) {
        len++;
    }
    return i + len;
}

int solve(int i, int p, int k) {
    int j = find_j(i, p);
    int cost = n - j;

    if (i == k) return cost;

    int dist = abs(i - k);
    cost += dist;

    return cost;
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", S);

    for (int t = 0; t < q; t++) {
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);
        printf("%d\n", solve(i - 1, p - 1, k - 1));
    }

    return 0;
}