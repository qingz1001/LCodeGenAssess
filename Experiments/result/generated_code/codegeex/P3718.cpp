#include <stdio.h>
#include <string.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    char s[100005];
    scanf("%s", s);

    int maxn = 0, cnt = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == s[i - 1] || i == 0) {
            cnt++;
        } else {
            cnt = 1;
        }
        maxn = fmax(maxn, cnt);
    }

    if (maxn <= k) {
        printf("1\n");
        return 0;
    }

    for (int i = 1; i <= maxn - k; i++) {
        ans += (maxn - k) / i;
    }

    printf("%d\n", ans);
    return 0;
}