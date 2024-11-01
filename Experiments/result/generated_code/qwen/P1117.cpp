#include <stdio.h>
#include <string.h>

#define MAXN 30005

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char S[MAXN];
        scanf("%s", S);
        int n = strlen(S);
        long long count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n - 1; j++) {
                if (j - i > n / 2) break;
                int k = j;
                int a_count = 0, b_count = 0;
                int valid = 1;
                while (k < n && valid) {
                    if (k - i == j - i) {
                        a_count++;
                        k += j - i;
                    } else {
                        b_count++;
                        k += j - i;
                    }
                    if (k < n && S[k] != S[k - (j - i)]) {
                        valid = 0;
                    }
                }
                if (valid && a_count > 0 && b_count > 0) {
                    count++;
                }
            }
        }

        printf("%lld\n", count);
    }
    return 0;
}