#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, c;
        scanf("%d %d %d", &n, &m, &c);

        if (c == n * m) {
            printf("-1\n");
            continue;
        }

        if (n == 1 || m == 1) {
            if (c >= 2) {
                printf("1\n");
            } else {
                printf("-1\n");
            }
            continue;
        }

        if (c >= 3) {
            printf("1\n");
        } else if (c == 2) {
            if (n == 2 || m == 2) {
                printf("-1\n");
            } else {
                printf("1\n");
            }
        } else if (c == 1) {
            if (n == 2 || m == 2) {
                printf("1\n");
            } else {
                printf("-1\n");
            }
        } else {
            printf("-1\n");
        }
    }

    return 0;
}