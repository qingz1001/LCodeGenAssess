#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005

char s[MAX_N];
int v[MAX_N], n;
int sa[MAX_N], rk[MAX_N], tmp[MAX_N], cnt[MAX_N];
int height[MAX_N];
int st[20][MAX_N], lg2[MAX_N];

typedef struct {
    int l, r;
} Segment;

Segment ans[MAX_N];
int ans_cnt = 0;

void get_sa() {
    int m = 128;
    for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
    for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
    
    for (int w = 1; w < n; w <<= 1) {
        int p = 0;
        for (int i = n; i > n-w; i--) tmp[++p] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > w) tmp[++p] = sa[i] - w;
        
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[tmp[i]]]--] = tmp[i];
        
        memcpy(tmp, rk, sizeof(rk));
        p = 0;
        for (int i = 1; i <= n; i++) {
            if (tmp[sa[i]] == tmp[sa[i-1]] && tmp[sa[i]+w] == tmp[sa[i-1]+w])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        }
        m = p;
        if (m == n) break;
    }
}

void get_height() {
    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (k) k--;
        while (s[i+k] == s[sa[rk[i]-1]+k]) k++;
        height[rk[i]] = k;
    }
}

void init_st() {
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i>>1] + 1;
    for (int i = 1; i <= n; i++) st[0][i] = height[i];
    for (int j = 1; j <= 19; j++)
        for (int i = 1; i + (1<<j) - 1 <= n; i++)
            st[j][i] = (st[j-1][i] < st[j-1][i+(1<<(j-1))] ? st[j-1][i] : st[j-1][i+(1<<(j-1))]);
}

int query(int l, int r) {
    int k = lg2[r-l+1];
    return (st[k][l] < st[k][r-(1<<k)+1] ? st[k][l] : st[k][r-(1<<k)+1]);
}

int get_lcp(int x, int y) {
    if (x == y) return n - x + 1;
    x = rk[x], y = rk[y];
    if (x > y) {int t = x; x = y; y = t;}
    return query(x+1, y);
}

int sum[MAX_N];

int main() {
    scanf("%s", s+1);
    n = strlen(s+1);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    
    get_sa();
    get_height();
    init_st();
    
    for (int i = 1; i <= n; i++) sum[i] = sum[i-1] + v[i];
    
    for (int i = 1; i <= n; i++) {
        int l = i, r = n, pos = i;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (sum[mid] - sum[i-1] <= n - rk[i] + 1) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (sum[pos] - sum[i-1] == n - rk[i] + 1) {
            ans[++ans_cnt] = (Segment){i, pos};
        }
    }
    
    printf("%d\n", ans_cnt);
    for (int i = 1; i <= ans_cnt; i++) {
        printf("%d %d\n", ans[i].l, ans[i].r);
    }
    
    return 0;
}