#include <stdio.h>
#include <string.h>

#define MAX_N 31
#define MAX_V 20001

int V, n;
int items[MAX_N];
int dp[MAX_V];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &V);
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &items[i]);
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = V; j >= items[i]; j--) {
            dp[j] = min(dp[j], dp[j - items[i]] + items[i]);
        }
    }
    
    int min_space = V;
    for (int i = 0; i <= V; i++) {
        if (dp[i] <= V) {
            min_space = min(min_space, V - dp[i]);
        }
    }
    
    printf("%d\n", min_space);
    
    return 0;
}