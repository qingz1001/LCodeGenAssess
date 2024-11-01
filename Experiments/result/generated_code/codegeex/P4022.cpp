#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 1100010;
char s[N], t[N];
int n, m, sa[N], rk[N], height[N], tax[N], tp[N], a[N], cnt[N];

void rixs() {
    for (int i = 1; i <= n; i++) tax[rk[i]]++;
    for (int i = 1; i <= m; i++) tax[i] += tax[i - 1];
    for (int i = n; i >= 1; i--) sa[tax[rk[tp[i]]]--] = tp[i];
}

void get_sa() {
    m = 128;
    for (int i = 1; i <= n; i++) rk[i] = a[i], tp[i] = i;
    rixs();
    for (int w = 1, p = 0; p < n; m = p, w <<= 1) {
        p = 0;
        for (int i = 1; i <= w; i++) tp[++p] = n - w + i;
        for (int i = 1; i <= n; i++) if (sa[i] > w) tp[++p] = sa[i] - w;
        rixs();
        swap(rk, tp);
        rk[sa[1]] = p = 1;
        for (int i = 2; i <= n; i++)
            rk[sa[i]] = (tp[sa[i]] == tp[sa[i - 1]] && tp[sa[i] + w] == tp[sa[i - 1] + w]) ? p : ++p;
    }
    for (int i = 1, k = 0; i <= n; i++) {
        if (k) k--;
        while (a[i + k] == a[sa[rk[i] - 1] + k]) k++;
        height[rk[i]] = k;
    }
}

int lcp(int x, int y) {
    if (x == y) return n - x + 1;
    x = rk[x], y = rk[y];
    if (x > y) swap(x, y);
    return height[x + 1];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        for (int j = 1; j <= len; j++) a[(i - 1) * len + j] = s[j] - '0';
    }
    n = m * 1000;
    get_sa();
    for (int i = 1; i <= n; i++) cnt[height[i]]++;
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[height[i]]--] = i;
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1; i <= n; i++) {
        if (rk[i] == 1) continue;
        int j = sa[rk[i] - 1];
        int k = lcp(j, sa[rk[i]]);
        if (k > 0) t[rk[i]] = t[rk[i] - 1] + k;
    }
    for (int i = 1; i <= n; i++) {
        if (t[i] >= 90) printf("%d\n", (i - 1) / m + 1);
        else printf("0\n");
    }
    return 0;
}