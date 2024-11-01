#include <stdio.h>
#include <stdlib.h>

int n, maxLen, totalLen, len;
int sticks[65], used[65], target[65];
int ans;

void dfs(int num, int sum, int prev) {
    if (num == n) {
        ans = sum;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            if (sum + sticks[i] <= len) {
                used[i] = 1;
                target[num] = sticks[i];
                dfs(num + 1, sum + sticks[i], sticks[i]);
                if (ans) return;
                used[i] = 0;
            } else if (sum == len) {
                used[i] = 1;
                target[num] = sticks[i];
                dfs(num + 1, sticks[i], sticks[i]);
                if (ans) return;
                used[i] = 0;
            }
            if (sum > prev) {
                return;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
        totalLen += sticks[i];
        maxLen = (maxLen < sticks[i]) ? sticks[i] : maxLen;
    }

    for (len = maxLen; len <= totalLen; len++) {
        if (totalLen % len != 0) continue;
        for (int i = 0; i < n; i++) {
            used[i] = 0;
        }
        dfs(0, 0, 0);
        if (ans == totalLen) {
            printf("%d\n", len);
            return 0;
        }
    }

    printf("%d\n", totalLen);
    return 0;
}