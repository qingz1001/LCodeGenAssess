#include <stdio.h>
#include <string.h>

#define MAX_N 30005

char s[MAX_N];
int n, ans;

void solve() {
    n = strlen(s);
    ans = 0;
    
    for (int len = 4; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            for (int k = i + 1; k < j; k++) {
                if ((k - i) * 2 > len) break;
                if ((k - i) * 2 == len) {
                    if (strncmp(s + i, s + k, k - i) == 0) {
                        ans++;
                    }
                } else {
                    int a_len = k - i;
                    int b_len = (len - 2 * a_len) / 2;
                    if (2 * a_len + 2 * b_len == len &&
                        strncmp(s + i, s + i + a_len, a_len) == 0 &&
                        strncmp(s + k, s + k + b_len, b_len) == 0) {
                        ans++;
                    }
                }
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        solve();
        printf("%d\n", ans);
    }
    return 0;
}