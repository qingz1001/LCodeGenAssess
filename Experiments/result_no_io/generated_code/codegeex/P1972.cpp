#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int a[MAXN], st[MAXN], top, n, m;
int ans[MAXN];

int read() {
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

int main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    m = read();
    for (int i = 1; i <= m; i++) {
        int l = read(), r = read();
        ans[i] = a[l];
    }
    top = 1;
    st[top] = 1;
    for (int i = 2; i <= n; i++) {
        while (top > 0 && a[st[top]] > a[i]) top--;
        if (top > 0) ans[st[top]] = a[i];
        st[++top] = i;
    }
    for (int i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}