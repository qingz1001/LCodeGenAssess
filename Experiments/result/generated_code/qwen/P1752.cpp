#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_M 200000

int n, m, p, q;
int dishes[MAX_M][2];
int picky[MAX_N], poor[MAX_N];

int main() {
    scanf("%d %d %d %d", &n, &m, &p, &q);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &dishes[i][0], &dishes[i][1]);
    }
    for (int i = 0; i < p; ++i) {
        scanf("%d", &picky[i]);
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d", &poor[i]);
    }

    int min_weeks = -1;
    for (int weeks = 1; weeks <= n; ++weeks) {
        int covered = 0;
        for (int i = 0; i < m; ++i) {
            int valid = 1;
            for (int j = 0; j < p && valid; ++j) {
                if (dishes[i][0] < picky[j]) {
                    valid = 0;
                }
            }
            for (int j = 0; j < q && valid; ++j) {
                if (dishes[i][1] > poor[j]) {
                    valid = 0;
                }
            }
            if (valid) {
                ++covered;
            }
        }
        if (covered == m) {
            min_weeks = weeks;
            break;
        }
    }

    printf("%d\n", min_weeks);

    return 0;
}