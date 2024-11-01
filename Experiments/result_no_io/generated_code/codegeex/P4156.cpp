#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 1000005

char str[MAXN];
int n, w, nxt[MAXN], len[MAXN];
long long ans;

void manacher(char *str, int n) {
    int id = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        if (i < mx) nxt[i] = (nxt[2 * id - i] < mx - i) ? nxt[2 * id - i] : mx - i;
        else nxt[i] = 1;
        while (i - nxt[i] >= 1 && i + nxt[i] <= n && str[i - nxt[i]] == str[i + nxt[i]]) nxt[i]++;
        if (i + nxt[i] > mx) {
            mx = i + nxt[i];
            id = i;
        }
    }
    for (int i = 1; i <= n; i++) len[i] = nxt[i] - 1;
}

bool check(int x) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (len[i] >= x) cnt++;
    }
    return cnt >= 2;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &w);
        scanf("%s", str + 1);
        manacher(str, n);
        if (w < n) {
            printf("0\n");
            continue;
        }
        ans = 0;
        for (int i = n; i <= w; i++) {
            if (check(i)) ans++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}