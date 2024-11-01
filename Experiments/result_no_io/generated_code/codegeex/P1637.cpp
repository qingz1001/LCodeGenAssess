#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXV 100005

int a[MAXN];
int s[MAXV];

int main() {
    int n, i, j, k, ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (i = 1; i <= n; i++) {
        s[a[i]]++;
    }

    for (i = 1; i <= 100000; i++) {
        s[i] += s[i - 1];
    }

    for (i = 1; i <= n; i++) {
        a[i] = s[a[i]] - 1;
    }

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (a[i] >= a[j]) continue;
            for (k = j + 1; k <= n; k++) {
                if (a[j] >= a[k]) continue;
                ans++;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}