#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 200005

int n, m;
int deg[MAX_N];
int edge[MAX_M][2];

long long C(int n, int k) {
    if (k > n) return 0;
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edge[i][0], &edge[i][1]);
        deg[edge[i][0]]++;
        deg[edge[i][1]]++;
    }
    
    long long red = 0;
    for (int i = 0; i < m; i++) {
        red += (long long)(deg[edge[i][0]] - 1) * (deg[edge[i][1]] - 1);
    }
    red /= 2;
    
    long long total = C(n, 4);
    long long blue = total - red;
    
    printf("%lld\n", llabs(blue - red));
    
    return 0;
}