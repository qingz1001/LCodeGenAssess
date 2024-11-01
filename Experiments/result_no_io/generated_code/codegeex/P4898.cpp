#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001

int h, w, q;
int r[MAXN], c[MAXN];
int idx[MAXN];
int cnt[MAXN];
int ans;

int main() {
    scanf("%d%d%d", &h, &w, &q);
    int n = h * w;

    // 读取初始座位表
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &r[i], &c[i]);
        r[i] *= w;
        c[i] += r[i];
        idx[c[i]] = i;
    }

    // 计算初始美妙度
    for (int i = 0; i < n; i++) {
        if (!cnt[r[i]]) {
            int l = r[i], r = r[i];
            while (l > 0 && cnt[l - 1] == cnt[l] - 1) l--;
            while (r < n && cnt[r] == cnt[r + 1] - 1) r++;
            ans += r - l + 1;
        }
        if (!cnt[c[i]]) {
            int l = c[i], r = c[i];
            while (l > 0 && cnt[l - 1] == cnt[l] - 1) l--;
            while (r < n && cnt[r] == cnt[r + 1] - 1) r++;
            ans += r - l + 1;
        }
        cnt[c[i]]++;
    }

    // 处理交换请求
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a = idx[a];
        b = idx[b];
        int ac = c[a], bc = c[b];
        cnt[ac]--;
        cnt[bc]++;
        if (!cnt[ac]) {
            int l = ac, r = ac;
            while (l > 0 && cnt[l - 1] == cnt[l] - 1) l--;
            while (r < n && cnt[r] == cnt[r + 1] - 1) r++;
            ans -= r - l + 1;
        }
        if (!cnt[bc]) {
            int l = bc, r = bc;
            while (l > 0 && cnt[l - 1] == cnt[l] - 1) l--;
            while (r < n && cnt[r] == cnt[r + 1] - 1) r++;
            ans -= r - l + 1;
        }
        if (ac != bc) {
            c[a] = bc;
            c[b] = ac;
            idx[a] = bc;
            idx[b] = ac;
        }
        if (!cnt[ac]) {
            int l = ac, r = ac;
            while (l > 0 && cnt[l - 1] == cnt[l] - 1) l--;
            while (r < n && cnt[r] == cnt[r + 1] - 1) r++;
            ans += r - l + 1;
        }
        if (!cnt[bc]) {
            int l = bc, r = bc;
            while (l > 0 && cnt[l - 1] == cnt[l] - 1) l--;
            while (r < n && cnt[r] == cnt[r + 1] - 1) r++;
            ans += r - l + 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}