#include <stdio.h>
#include <string.h>

#define MAXN 30010

char s[MAXN];
int nxt1[MAXN], nxt2[MAXN];
long long ans;

void solve() {
    int n = strlen(s);
    int i, j, k;
    ans = 0;

    // 计算每个位置的最长相同前后缀长度
    for (i = 1, j = 0, k = 1; k < n; k++) {
        while (j > 0 && s[j] != s[k]) j = nxt1[j - 1];
        if (s[j] == s[k]) j++;
        nxt1[k] = j;
    }

    // 计算每个位置的最长相同前后缀长度
    for (i = n - 2, j = 0, k = n - 2; k >= 0; k--) {
        while (j > 0 && s[j] != s[k]) j = nxt2[j - 1];
        if (s[j] == s[k]) j++;
        nxt2[k] = j;
    }

    // 统计优秀拆分的总个数
    for (i = 0; i < n - 1; i++) {
        if (nxt1[i] != 0 && nxt2[i + 1] != 0) {
            if (nxt1[i] + i <= n - nxt2[i + 1]) {
                ans += (nxt1[i] + i - n + nxt2[i + 1]) / 2;
            }
        }
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        solve();
    }
    return 0;
}