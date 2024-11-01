#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 500
#define MAXK 20
#define INF 1000000

int n;
int a[MAX];
int dp_cache[501][501][21];

int min(int x, int y) {
    return x < y ? x : y;
}

int dp(int i, int j, int k) {
    if (i > j) return 0;
    if (k > 20) k = 20; // Cap k to prevent overflow
    if (dp_cache[i][j][k] != -1) return dp_cache[i][j][k];
    
    // Initialize result by removing the last bead with necessary insertions
    int res;
    if (k +1 >= 3)
        res = dp(i, j-1, 0);
    else
        res = (3 - (k +1)) + dp(i, j-1, 0);
    
    // Try to merge beads of the same color
    for(int m = i; m < j; m++) {
        if(a[m] == a[j]) {
            int cost = dp(i, m, k +1) + dp(m+1, j-1, 0);
            if(cost < res)
                res = cost;
        }
    }
    
    dp_cache[i][j][k] = res;
    return res;
}

int main(){
    memset(dp_cache, -1, sizeof(dp_cache));
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    printf("%d\n", dp(0, n-1, 0));
    return 0;
}