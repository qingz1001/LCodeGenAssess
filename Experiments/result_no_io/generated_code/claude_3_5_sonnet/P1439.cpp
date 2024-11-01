#include <stdio.h>
#include <string.h>

#define MAX_N 100005

int n;
int p1[MAX_N], p2[MAX_N];
int pos[MAX_N];
int dp[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p1[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p2[i]);
        pos[p2[i]] = i;
    }
    
    int len = 0;
    for (int i = 1; i <= n; i++) {
        int j = pos[p1[i]];
        int k = 0;
        for (int l = 1; l <= len; l++) {
            if (dp[l] < j) {
                k = l;
                break;
            }
        }
        if (k == 0) k = ++len;
        dp[k] = j;
    }
    
    printf("%d\n", len);
    
    return 0;
}