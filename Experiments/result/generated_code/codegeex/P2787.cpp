#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[50005];
int n, m;

int main() {
    scanf("%d%d%s", &n, &m, s + 1);
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        char k;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            scanf(" %c", &k);
            int cnt = 0;
            for (int j = x; j <= y; j++) {
                if (tolower(s[j]) == tolower(k)) {
                    cnt++;
                }
            }
            printf("%d\n", cnt);
        } else if (op == 2) {
            scanf(" %c", &k);
            for (int j = x; j <= y; j++) {
                s[j] = k;
            }
        } else if (op == 3) {
            for (int j = x; j <= y; j++) {
                for (int k = j + 1; k <= y; k++) {
                    if (s[j] > s[k]) {
                        char tmp = s[j];
                        s[j] = s[k];
                        s[k] = tmp;
                    }
                }
            }
        }
    }
    return 0;
}