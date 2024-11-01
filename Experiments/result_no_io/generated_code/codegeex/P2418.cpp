#include <stdio.h>
#include <limits.h>

#define MAXN 500005

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    
    int a[MAXN];
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    
    int dp[MAXN];
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= N; i++) {
        int minn = INT_MAX;
        for (int j = i - 1; j >= 0; j--) {
            int cnt1 = 0, cnt2 = 0;
            for (int k = j; k <= i; k++) {
                if (a[k] == 1) cnt1++;
                else cnt2++;
            }
            int diff = abs(cnt1 - cnt2);
            if (diff <= M) {
                minn = dp[j] + 1;
                break;
            }
        }
        dp[i] = minn;
    }
    
    printf("%d\n", dp[N]);
    return 0;
}