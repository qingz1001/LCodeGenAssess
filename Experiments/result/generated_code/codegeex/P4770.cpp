#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 500005

char s[MAXN], t[MAXN];
int sa[MAXN], rk[MAXN], height[MAXN], c[MAXN], tmp[MAXN], n, m, q;
int l[MAXN], r[MAXN], len[MAXN];

void build_sa() {
    int i, j, p;
    for (i = 0; i <= m; i++) c[i] = 0;
    for (i = 0; i < n; i++) c[rk[i] = s[i]]++;
    for (i = 1; i <= m; i++) c[i] += c[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--c[rk[i]]] = i;
    for (p = 1; p < n; p <<= 1) {
        for (i = 0; i < n; i++) {
            j = sa[i] - p;
            if (j < 0) j += n;
            tmp[c[rk[j]]++] = j;
        }
        sa[tmp[c[0] = 0]] = j = 0;
        for (i = 1; i < n; i++) {
            if (rk[tmp[i]] != rk[tmp[i - 1]] || rk[tmp[i] + p] != rk[tmp[i - 1] + p]) c[++j] = i;
            sa[tmp[i]] = j;
        }
        memcpy(rk, sa, n * sizeof(int));
        m = j;
    }
}

void build_height() {
    int i, j, k = 0;
    for (i = 0; i < n; i++) rk[sa[i]] = i;
    for (i = 0; i < n; height[rk[i++]] = k)
        for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
}

int find(int x) {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (height[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    m = 255;
    build_sa();
    build_height();
    
    scanf("%d", &q);
    while (q--) {
        scanf("%s%d%d", t, &l[q], &r[q]);
        len[q] = strlen(t);
        for (int i = 0; i < len[q]; i++) rk[i] = t[i];
        m = 255;
        build_sa();
        build_height();
        
        int ans = 0;
        for (int i = 0; i < len[q]; i++) {
            int pos = find(i + 1);
            if (pos >= l[q] && pos <= r[q]) continue;
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}