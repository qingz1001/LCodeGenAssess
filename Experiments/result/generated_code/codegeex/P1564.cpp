#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[2501], dp[2501];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        int count1 = 0, count2 = 0;
        for (int j = i; j <= n; j++) {
            if (a[j] == 1) {
                count1++;
            } else {
                count2++;
            }
            int diff = count1 - count2;
            if (diff < 0) {
                diff = -diff;
            }
            if (diff <= m) {
                dp[j] = dp[i-1] + 1;
            }
        }
    }
    
    int min_rooms = dp[n];
    for (int i = 1; i <= n; i++) {
        if (dp[i] < min_rooms) {
            min_rooms = dp[i];
        }
    }
    
    printf("%d\n", min_rooms);
    return 0;
}