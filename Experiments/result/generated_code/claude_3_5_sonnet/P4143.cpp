#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005

char s[MAX_N];
int v[MAX_N], n;
int sa[MAX_N], rk[MAX_N], tmp[MAX_N], cnt[MAX_N];
int height[MAX_N];
int sum[MAX_N];

void get_sa() {
    int m = 128;
    for (int i = 0; i < m; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; i--) sa[--cnt[s[i]]] = i;
    rk[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
        rk[sa[i]] = rk[sa[i-1]];
        if (s[sa[i]] != s[sa[i-1]]) rk[sa[i]]++;
    }
    for (int w = 1; w < n; w *= 2) {
        int k = 0;
        for (int i = n-w; i < n; i++) tmp[k++] = i;
        for (int i = 0; i < n; i++) if (sa[i] >= w) tmp[k++] = sa[i] - w;
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[rk[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];
        memcpy(tmp, rk, n * sizeof(int));
        rk[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            rk[sa[i]] = rk[sa[i-1]];
            if (tmp[sa[i]] != tmp[sa[i-1]] || tmp[sa[i]+w] != tmp[sa[i-1]+w]) rk[sa[i]]++;
        }
        m = rk[sa[n-1]] + 1;
        if (m == n) break;
    }
}

void get_height() {
    int k = 0;
    for (int i = 0; i < n-1; i++) {
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (s[i+k] == s[j+k]) k++;
        height[rk[i]] = k;
    }
}

typedef struct {
    int l, r;
} Pair;

Pair result[MAX_N];
int result_count = 0;

void solve() {
    get_sa();
    get_height();
    
    for (int i = 1; i <= n; i++) sum[i] = sum[i-1] + v[i-1];
    
    for (int i = 0; i < n; i++) {
        int l = sa[i] + 1, r = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            int rank = n - i;
            int total = sum[mid] - sum[sa[i]];
            if (rank == total) {
                result[result_count].l = sa[i] + 1;
                result[result_count].r = mid;
                result_count++;
                l = mid + 1;
            } else if (rank < total) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
}

int cmp(const void *a, const void *b) {
    Pair *pa = (Pair*)a;
    Pair *pb = (Pair*)b;
    if (pa->l != pb->l) return pa->l - pb->l;
    return pa->r - pb->r;
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    
    solve();
    
    qsort(result, result_count, sizeof(Pair), cmp);
    
    printf("%d\n", result_count);
    for (int i = 0; i < result_count; i++) {
        printf("%d %d\n", result[i].l, result[i].r);
    }
    
    return 0;
}