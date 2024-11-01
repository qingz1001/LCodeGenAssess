#include <stdio.h>
#include <string.h>

#define MAXN 100005

char s[MAXN];
int sa[MAXN], rk[MAXN], height[MAXN];
int cnt[MAXN], oldrk[MAXN], oldsa[MAXN];

// 基数排序
void build_sa(int n) {
    int m = 26;
    for (int i = 0; i <= m; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n - k + 1; i <= n; i++) oldsa[++p] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) oldsa[++p] = sa[i] - k;
        for (int i = 0; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[oldrk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[oldrk[oldsa[i]]]--] = oldsa[i];
        for (int i = 1; i <= n; i++) oldrk[i] = rk[i];
        p = 0;
        for (int i = 1; i <= n; i++) {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + k] == oldrk[sa[i - 1] + k]) rk[sa[i]] = p;
            else rk[sa[i]] = ++p;
        }
        if (p == n) break;
        m = p;
    }
}

// 计算height数组
void build_height(int n) {
    int k = 0;
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1; i <= n; i++) {
        if (rk[i] == 1) continue;
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        height[rk[i]] = k;
    }
}

// 二分查找
int find(int x, int y, int len) {
    int l = 1, r = y - x + 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (height[mid] >= len) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    build_sa(n);
    build_height(n);
    while (m--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int l = 0, r = b - a + 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            int pos = find(a, b, mid);
            int k = b - pos + 1;
            if (k > d - c + 1) {
                r = mid - 1;
            } else if (k == d - c + 1) {
                l = mid;
            } else {
                l = mid;
            }
        }
        printf("%d\n", l);
    }
    return 0;
}