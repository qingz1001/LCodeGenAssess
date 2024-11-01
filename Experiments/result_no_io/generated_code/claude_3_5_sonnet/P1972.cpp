#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define BLOCK_SIZE 1000

int n, m, block_num;
int a[MAXN], belong[MAXN], L[MAXN], R[MAXN];
int cnt[MAXN], num[MAXN];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

void init() {
    block_num = n / BLOCK_SIZE;
    if (n % BLOCK_SIZE) block_num++;
    
    for (int i = 1; i <= n; i++) {
        belong[i] = (i - 1) / BLOCK_SIZE + 1;
        if (L[belong[i]] == 0) L[belong[i]] = i;
        R[belong[i]] = i;
    }
}

int query(int l, int r) {
    int res = 0;
    memset(cnt, 0, sizeof(cnt));
    
    if (belong[l] == belong[r]) {
        for (int i = l; i <= r; i++) {
            if (cnt[a[i]] == 0) res++;
            cnt[a[i]]++;
        }
        return res;
    }
    
    for (int i = l; i <= R[belong[l]]; i++) {
        if (cnt[a[i]] == 0) res++;
        cnt[a[i]]++;
    }
    
    for (int i = belong[l] + 1; i < belong[r]; i++) {
        res += num[i];
        for (int j = L[i]; j <= R[i]; j++) {
            cnt[a[j]]++;
        }
    }
    
    for (int i = L[belong[r]]; i <= r; i++) {
        if (cnt[a[i]] == 0) res++;
        cnt[a[i]]++;
    }
    
    return res;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    
    init();
    
    for (int i = 1; i <= block_num; i++) {
        int tmp[MAXN] = {0};
        for (int j = L[i]; j <= R[i]; j++) {
            if (tmp[a[j]] == 0) num[i]++;
            tmp[a[j]] = 1;
        }
    }
    
    m = read();
    for (int i = 1; i <= m; i++) {
        int l = read(), r = read();
        printf("%d\n", query(l, r));
    }
    
    return 0;
}