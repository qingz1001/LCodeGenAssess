#include <stdio.h>
#include <string.h>

#define MAX_N 30005

char s[MAX_N];
int n, ans;

void solve() {
    ans = 0;
    n = strlen(s);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int len = j - i + 1;
            if (len % 2 == 0) {
                int half = len / 2;
                for (int k = 1; k <= half / 2; k++) {
                    if (half % k == 0) {
                        int flag = 1;
                        for (int p = 0; p < k; p++) {
                            for (int q = 0; q < half / k; q++) {
                                if (s[i + p + q * k] != s[i + k + p + q * k]) {
                                    flag = 0;
                                    break;
                                }
                            }
                            if (!flag) break;
                        }
                        if (flag) {
                            for (int p = 0; p < k; p++) {
                                for (int q = 0; q < half / k; q++) {
                                    if (s[i + half + p + q * k] != s[i + half + k + p + q * k]) {
                                        flag = 0;
                                        break;
                                    }
                                }
                                if (!flag) break;
                            }
                            if (flag) ans++;
                        }
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