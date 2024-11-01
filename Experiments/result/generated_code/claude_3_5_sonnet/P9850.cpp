#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 200005

int n, m;
int deg[MAX_N];
int edges[MAX_M][2];

long long C(int n, int k) {
    if (k > n - k) k = n - k;
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        res *= n - k + i;
        res /= i;
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
        deg[edges[i][0]]++;
        deg[edges[i][1]]++;
    }

    long long total = C(n, 4);
    long long blue = total;

    long long red_tri = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        red_tri += n - deg[u] - deg[v] + 1;
    }
    red_tri /= 3;

    long long blue_tri = C(n, 3) - m * (n - 2) + red_tri;

    for (int i = 1; i <= n; i++) {
        blue -= C(deg[i], 3);
    }
    blue += 3 * red_tri;

    long long red = total - blue;

    printf("%lld\n", llabs(blue - red));

    return 0;
}