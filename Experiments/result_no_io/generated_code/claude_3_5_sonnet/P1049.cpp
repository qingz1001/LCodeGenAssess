#include <stdio.h>

#define MAX_N 30
#define MAX_V 20000

int V, n;
int items[MAX_N];
int dp[MAX_V + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &V);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &items[i]);
    }
    
    for (int i = 0; i <= V; i++) {
        dp[i] = i;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = V; j >= items[i]; j--) {
            dp[j] = min(dp[j], dp[j - items[i]]);
        }
    }
    
    printf("%d\n", dp[V]);
    
    return 0;
}