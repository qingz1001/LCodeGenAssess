#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 200005
#define MAXM 200005

typedef long long ll;

int n, m;
ll s;
int w[MAXN], v[MAXN];
int l[MAXM], r[MAXM];
int sorted_w[MAXN];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

ll calc(int W) {
    static int cnt[MAXN], sum[MAXN];
    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));
    
    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i-1] + (w[i] >= W);
        sum[i] = sum[i-1] + (w[i] >= W ? v[i] : 0);
    }
    
    ll res = 0;
    for (int i = 0; i < m; i++) {
        int count = cnt[r[i]] - cnt[l[i]-1];
        ll total = sum[r[i]] - sum[l[i]-1];
        res += (ll)count * total;
    }
    return res;
}

int main() {
    scanf("%d%d%lld", &n, &m, &s);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &v[i]);
        sorted_w[i] = w[i];
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &l[i], &r[i]);
    }
    
    qsort(sorted_w + 1, n, sizeof(int), cmp);
    
    int left = 1, right = n;
    ll res = LLONG_MAX;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int W = sorted_w[mid];
        ll y = calc(W);
        
        res = llabs(s - y) < res ? llabs(s - y) : res;
        
        if (y > s) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    printf("%lld\n", res);
    
    return 0;
}