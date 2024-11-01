#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAX_N 20005
#define MAX_M 1000005

int n, k;
int a[MAX_N], b[MAX_N], sa[MAX_N], rk[MAX_N], height[MAX_N];
int c[MAX_N], oldrk[MAX_N], oldsa[MAX_N];

void build_sa() {
    int m = MAX_M;
    for (int i = 0; i < n; i++) c[rk[i] = a[i]]++;
    for (int i = 1; i < m; i++) c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--c[rk[i]]] = i;

    for (int k = 1; k < n; k <<= 1) {
        int p = 0;
        for (int i = n - k; i < n; i++) oldsa[p++] = i;
        for (int i = 0; i < n; i++) if (sa[i] >= k) oldsa[p++] = sa[i] - k;

        memset(c, 0, sizeof(c));
        for (int i = 0; i < n; i++) c[oldrk[i]]++;
        for (int i = 1; i < m; i++) c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--c[oldrk[oldsa[i]]]] = oldsa[i];

        std::swap(rk, oldrk);
        p = rk[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            rk[sa[i]] = (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + k] == oldrk[sa[i - 1] + k]) ? p : ++p;
        if (p == n - 1) break;
        m = p + 1;
    }
}

void build_height() {
    int k = 0;
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    for (int i = 0; i < n; i++) {
        if (rk[i] == 0) continue;
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (i + k < n && j + k < n && a[i + k] == a[j + k]) k++;
        height[rk[i]] = k;
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    build_sa();
    build_height();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i + k - 1 >= n) break;
        int len = height[i];
        int cnt = 1;
        for (int j = i + 1; j < n; j++) {
            if (height[j] < len) len = height[j];
            if (height[j] < k) break;
            cnt++;
        }
        if (cnt >= k) ans = std::max(ans, len);
    }

    printf("%d\n", ans);
    return 0;
}