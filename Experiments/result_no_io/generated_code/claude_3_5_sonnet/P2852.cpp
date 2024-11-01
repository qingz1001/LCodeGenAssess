#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 20005
#define MAXM 1000005

int N, K;
int milk[MAXN];
int sa[MAXN], rk[MAXN], tp[MAXN], tax[MAXM], height[MAXN];

void radix_sort(int *sa, int *x, int m) {
    int i, *y = tp;
    memset(tax, 0, sizeof(int) * (m + 1));
    for (i = 0; i < N; i++) tax[x[i]]++;
    for (i = 1; i <= m; i++) tax[i] += tax[i - 1];
    for (i = N - 1; i >= 0; i--) sa[--tax[x[i]]] = i;
}

void build_sa(int m) {
    int i, k, p, *x = rk, *y = tp;
    for (i = 0; i < N; i++) x[i] = milk[i], y[i] = i;
    radix_sort(sa, x, m);
    for (k = 1, p = 1; p < N; k *= 2, m = p) {
        for (p = 0, i = N - k; i < N; i++) y[p++] = i;
        for (i = 0; i < N; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
        radix_sort(sa, x, m);
        for (i = 0; i < N; i++) tp[i] = x[i];
        for (p = 0, i = 1; i < N; i++)
            x[sa[i]] = (tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+k] == tp[sa[i-1]+k]) ? p : ++p;
    }
}

void get_height() {
    int i, k = 0;
    for (i = 0; i < N; i++) rk[sa[i]] = i;
    for (i = 0; i < N; i++) {
        if (k) k--;
        if (rk[i] == 0) continue;
        int j = sa[rk[i] - 1];
        while (i + k < N && j + k < N && milk[i+k] == milk[j+k]) k++;
        height[rk[i]] = k;
    }
}

int check(int len) {
    int cnt = 1;
    for (int i = 1; i < N; i++) {
        if (height[i] >= len) cnt++;
        else {
            if (cnt >= K) return 1;
            cnt = 1;
        }
    }
    return cnt >= K;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &milk[i]);
    }

    build_sa(MAXM);
    get_height();

    int left = 0, right = N, ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}