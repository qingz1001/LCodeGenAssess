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
            int i = 0;
            while (i < n) {
                if (s[i] == '1') {
                    operations++;
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