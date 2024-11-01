#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 50005

char s[MAXN];
int n, m;

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s + 1);

    for (int i = 1; i <= m; i++) {
        int op, x, y;
        char k;
        scanf("%d %d %d", &op, &x, &y);

        if (op == 1) {
            scanf(" %c", &k);
            int count = 0;
            for (int j = x; j <= y; j++) {
                if (tolower(s[j]) == tolower(k)) {
                    count++;
                }
            }
            printf("%d\n", count);
        } else if (op == 2) {
            scanf(" %c", &k);
            for (int j = x; j <= y; j++) {
                s[j] = k;
            }
        } else if (op == 3) {
            for (int j = x; j <= y; j++) {
                for (int k = j + 1; k <= y; k++) {
                    if (s[j] > s[k]) {
                        char temp = s[j];
                        s[j] = s[k];
                        s[k] = temp;
                    }
                }
            }
        }
    }

    return 0;
}