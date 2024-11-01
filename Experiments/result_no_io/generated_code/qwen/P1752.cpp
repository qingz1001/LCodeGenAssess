#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_M 200000

int n, m, p, q;
int dishes[MAX_M][2];
int picky[MAX_N];
int poor[MAX_N];

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
    int total_dishes = 0;

    for (int week = 1; week <= n; ++week) {
        int count = 0;
        for (int i = 0; i < m; ++i) {
            if ((picky[0] == 0 || dishes[i][0] >= picky[0]) && (poor[0] == 0 || dishes[i][1] <= poor[0])) {
                count++;
            }
        }
        total_dishes += count;
        if (total_dishes >= m) {
            min_weeks = week;
            break;
        }
    }

    printf("%d\n", min_weeks);

    return 0;
}