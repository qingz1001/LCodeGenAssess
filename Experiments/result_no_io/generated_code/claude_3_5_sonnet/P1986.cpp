#include <stdio.h>
#include <string.h>

#define MAXN 30001
#define MAXM 5001

int n, m;
int diff[MAXN];
int need[MAXM], a[MAXM], b[MAXM], c[MAXM];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(diff, 0, sizeof(diff));
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
        need[i] = c[i];
        diff[a[i]] += c[i];
        diff[b[i] + 1] -= c[i];
    }
    
    int sum = 0, res = 0;
    for (int i = 1; i <= n; i++) {
        sum += diff[i];
        res = max(res, sum);
    }
    
    printf("%d\n", res);
    
    return 0;
}