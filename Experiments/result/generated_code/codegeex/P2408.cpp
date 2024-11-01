#include <stdio.h>
#include <string.h>

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);
    char s[100005];
    scanf("%s", s);

    int sa[100005], rk[100005], cnt[100005], id[100005], px[100005];
    ll ans = 0;

    // 初始化
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rk[i] = s[i] - 'a';
    }

    // 倍增算法求后缀数组
    for (int w = 1; w < n; w <<= 1) {
        int num = 0;
        for (int i = 0; i < n; i++) {
            if (i + w >= n) id[i] = -1;
            else id[i] = rk[i + w];
            px[i] = rk[i];
        }
        for (int i = 0; i < n; i++) cnt[px[i]]++;
        for (int i = 0; i < 26; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[px[i]]] = i;
        for (int i = 0; i < n; i++) rk[sa[i]] = (rk[sa[i]] == rk[sa[i - 1]] && id[sa[i]] == id[sa[i - 1]]) ? num : ++num;
    }

    // 计算不同子串的个数
    for (int i = 0; i < n; i++) {
        ans += n - sa[i];
    }

    printf("%lld\n", ans);
    return 0;
}