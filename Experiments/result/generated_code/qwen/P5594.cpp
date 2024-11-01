#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXM 1001
#define MAXK 1001

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int schedule[MAXN][MAXM];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &schedule[i][j]);
        }
    }

    int count[MAXK] = {0};
    for (int day = 0; day < k; day++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (schedule[i][j] == day + 1) {
                    count[day]++;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < k; i++) {
        printf("%d ", count[i]);
    }
    printf("\n");

    return 0;
}