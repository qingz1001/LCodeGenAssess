#include <stdio.h>
#include <string.h>

#define MAX_N 32001
#define MAX_M 61

int n, m;
int dp[MAX_N];
int v[MAX_M], p[MAX_M], q[MAX_M];
int main_item[MAX_M], sub1[MAX_M], sub2[MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(main_item, 0, sizeof(main_item));
    memset(sub1, 0, sizeof(sub1));
    memset(sub2, 0, sizeof(sub2));
    
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &v[i], &p[i], &q[i]);
        if (q[i] == 0) {
            main_item[i] = i;
        } else {
            if (sub1[q[i]] == 0) {
                sub1[q[i]] = i;
            } else {
                sub2[q[i]] = i;
            }
        }
    }
    
    for (int i = 1; i <= m; i++) {
        if (main_item[i] == 0) continue;
        
        for (int j = n; j >= v[i]; j--) {
            dp[j] = max(dp[j], dp[j - v[i]] + v[i] * p[i]);
            
            if (j >= v[i] + v[sub1[i]])
                dp[j] = max(dp[j], dp[j - v[i] - v[sub1[i]]] + v[i] * p[i] + v[sub1[i]] * p[sub1[i]]);
            
            if (j >= v[i] + v[sub2[i]])
                dp[j] = max(dp[j], dp[j - v[i] - v[sub2[i]]] + v[i] * p[i] + v[sub2[i]] * p[sub2[i]]);
            
            if (j >= v[i] + v[sub1[i]] + v[sub2[i]])
                dp[j] = max(dp[j], dp[j - v[i] - v[sub1[i]] - v[sub2[i]]] + v[i] * p[i] + v[sub1[i]] * p[sub1[i]] + v[sub2[i]] * p[sub2[i]]);
        }
    }
    
    printf("%d\n", dp[n]);
    
    return 0;
}