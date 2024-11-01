#include <stdio.h>
#include <string.h>

#define MOD 1000000009

int main() {
    char s[500005];
    scanf("%s", s);
    int n = strlen(s);
    int f[n + 1];
    memset(f, 0, sizeof(f));
    int i, j, k;
    for (i = 0; i < n; i++) {
        if (s[i] == 'B' || s[i] == '?') {
            for (j = i; j < n; j++) {
                if (s[j] == 'W' || s[j] == '?') {
                    if (j - i >= i) {
                        f[j + 1] = (f[j + 1] + f[i]) % MOD;
                    }
                    if (i) {
                        f[i] = (f[i] + f[i - 1]) % MOD;
                    }
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }
    printf("%d\n", f[n]);
    return 0;
}