#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005

int a[MAXN], n, m;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    char command[20];
    int posi, tot, c;

    for (int i = 0; i < m; i++) {
        scanf("%s", command);
        if (strcmp(command, "INSERT") == 0) {
            scanf("%d %d", &posi, &tot);
            for (int j = 0; j < tot; j++) {
                scanf("%d", &c);
                a[posi + j + 1] = c;
            }
            n += tot;
        } else if (strcmp(command, "DELETE") == 0) {
            scanf("%d %d", &posi, &tot);
            for (int j = posi; j <= n - tot; j++) {
                a[j] = a[j + tot];
            }
            n -= tot;
        } else if (strcmp(command, "MAKE-SAME") == 0) {
            scanf("%d %d %d", &posi, &tot, &c);
            for (int j = posi; j <= posi + tot - 1; j++) {
                a[j] = c;
            }
        } else if (strcmp(command, "REVERSE") == 0) {
            scanf("%d %d", &posi, &tot);
            for (int j = 0; j < tot / 2; j++) {
                int tmp = a[posi + j];
                a[posi + j] = a[posi + tot - j - 1];
                a[posi + tot - j - 1] = tmp;
            }
        } else if (strcmp(command, "GET-SUM") == 0) {
            scanf("%d %d", &posi, &tot);
            int sum = 0;
            for (int j = posi; j <= posi + tot - 1; j++) {
                sum += a[j];
            }
            printf("%d\n", sum);
        } else if (strcmp(command, "MAX-SUM") == 0) {
            int max_sum = -1001, current_sum = 0;
            for (int j = 1; j <= n; j++) {
                current_sum = (current_sum + a[j] > 0) ? current_sum + a[j] : 0;
                max_sum = (current_sum > max_sum) ? current_sum : max_sum;
            }
            printf("%d\n", max_sum);
        }
    }

    return 0;
}