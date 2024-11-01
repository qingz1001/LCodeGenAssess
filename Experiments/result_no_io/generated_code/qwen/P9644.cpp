#include <stdio.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        char s[n + 1];
        scanf("%s", s);

        int min_L = n;
        for (int L = 1; L <= n; L++) {
            int operations = 0;
            for (int i = 0; i < n;) {
                if (s[i] == '1') {
                    operations++;
                    for (int j = 0; j < L && i + j < n; j++) {
                        if (s[i + j] == '1') {
                            s[i + j] = '0';
                        }
                    }
                    i += L;
                } else {
                    i++;
                }
            }
            if (operations <= k) {
                min_L = L;
                break;
            }
        }

        printf("%d\n", min_L);
    }
    return 0;
}