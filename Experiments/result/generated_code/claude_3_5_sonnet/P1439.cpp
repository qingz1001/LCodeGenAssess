#include <stdio.h>
#include <string.h>

#define MAX_N 100005

int n;
int p1[MAX_N], p2[MAX_N];
int pos[MAX_N];
int dp[MAX_N];

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p1[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        pos[x] = i;
    }
    
    int len = 0;
    for (int i = 1; i <= n; i++) {
        int x = pos[p1[i]];
        int l = 1, r = len;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (dp[mid] < x) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        dp[l] = x;
        if (l > len) len = l;
    }
    
    printf("%d\n", len);
    
    return 0;
}