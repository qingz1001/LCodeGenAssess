#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500000
#define INF 0x3f3f3f3f

typedef long long ll;

int n, d;
ll k;
ll x[MAX_N + 1], s[MAX_N + 1];
ll dp[MAX_N + 1];

int binary_search(int l, int r, ll target) {
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (x[mid] <= target) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

int check(int g) {
    memset(dp, 0xc0, sizeof(dp));
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        int min_jump = (d - g > 1) ? d - g : 1;
        int max_jump = d + g;
        
        int l = binary_search(0, i - 1, x[i] - max_jump);
        int r = binary_search(0, i - 1, x[i] - min_jump);
        
        for (int j = l; j <= r; j++) {
            if (x[i] - x[j] >= min_jump && x[i] - x[j] <= max_jump) {
                dp[i] = (dp[i] > dp[j] + s[i]) ? dp[i] : dp[j] + s[i];
            }
        }
        
        if (dp[i] >= k) return 1;
    }
    
    return 0;
}

int main() {
    scanf("%d %d %lld", &n, &d, &k);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &x[i], &s[i]);
    }
    
    int l = 0, r = 2000;
    int result = -1;
    
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            result = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}