#include <stdio.h>
#include <string.h>

int n;
int a[300005];
int s[300005];
int sa[300005];
int rk[300005];
int cnt[300005];
int height[300005];

void get_sa() {
    int m = 30;
    for (int i = 0; i < n; i++) cnt[rk[i] = a[i]]++;
    for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[i]]] = i;
    for (int k = 1; k < n; k <<= 1) {
        int num = 0;
        for (int i = n - k; i < n; i++) s[num++] = i;
        for (int i = 0; i < n; i++) if (sa[i] >= k) s[num++] = sa[i] - k;
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[rk[s[i]]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[s[i]]]] = s[i];
        memcpy(s, rk, n * sizeof(int));
        rk[sa[0]] = num = 0;
        for (int i = 1; i < n; i++)
            rk[sa[i]] = s[sa[i]] == s[sa[i - 1]] && s[sa[i] + k] == s[sa[i - 1] + k] ? num : ++num;
        if (num == n - 1) break;
        m = num + 1;
    }
}

void get_height() {
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rk[i] > 0) {
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && a[i + k] == a[j + k]) k++;
        }
        height[rk[i]] = k;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    get_sa();
    get_height();
    int min_h = 0x3f3f3f3f, min_pos = 0;
    for (int i = 1; i < n; i++) {
        if (height[i] < min_h) {
            min_h = height[i];
            min_pos = i;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", a[(min_pos + i) % n]);
    }
    return 0;
}