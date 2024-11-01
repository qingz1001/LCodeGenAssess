#include <stdio.h>

#define MAXN 1005
#define MAXM 1005

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int schedule[MAXN][MAXM];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &schedule[i][j]);
        }
    }

    int result[MAXM] = {0};
    for (int day = 0; day < k; day++) {
        for (int i = 0; i < n; i++) {
            if (day == schedule[i][0]) {
                result[day]++;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}