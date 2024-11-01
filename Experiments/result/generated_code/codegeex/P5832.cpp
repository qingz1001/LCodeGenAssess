#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[101];
    scanf("%s", s);

    int k = 1;
    while (k <= n) {
        int flag = 0;
        for (int i = 0; i <= n - k; i++) {
            for (int j = i + 1; j <= n - k; j++) {
                int l;
                for (l = 0; l < k; l++) {
                    if (s[i + l] != s[j + l]) {
                        break;
                    }
                }
                if (l == k) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (!flag) {
            printf("%d\n", k);
            break;
        }
        k++;
    }

    return 0;
}