#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXM 30005

int main() {
    int k, m, n;
    scanf("%d %d %d", &k, &m, &n);

    int a[MAXM], b[MAXM];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &a[i], &b[i]);
    }

    int can_kill[MAXN] = {0};
    for (int i = 0; i < m; ++i) {
        if (a[i] <= k && n % a[i] == 0) {
            can_kill[i + 1] = 1;
        }
    }

    int first_skill = -1;
    for (int i = 1; i <= m; ++i) {
        if (can_kill[i]) {
            if (first_skill == -1) {
                first_skill = i;
            } else {
                printf("%d ", i);
            }
        }
    }

    if (first_skill != -1) {
        printf("%d\n", first_skill);
    } else {
        printf("-1\n");
    }

    return 0;
}