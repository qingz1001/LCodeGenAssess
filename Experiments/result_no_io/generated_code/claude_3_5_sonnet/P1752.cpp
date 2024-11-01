#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50000
#define MAX_M 200000

int n, m, p, q;
int delicious[MAX_M], price[MAX_M];
int picky[MAX_N], poor[MAX_N];
int can_eat[MAX_M];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d %d %d", &n, &m, &p, &q);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &delicious[i], &price[i]);
    }

    for (int i = 0; i < p; i++) {
        scanf("%d", &picky[i]);
    }

    for (int i = 0; i < q; i++) {
        scanf("%d", &poor[i]);
    }

    qsort(picky, p, sizeof(int), cmp);
    qsort(poor, q, sizeof(int), cmp);

    int total_can_eat = 0;
    for (int i = 0; i < m; i++) {
        int can_eat_count = n - p - q;

        int picky_can_eat = p - (int)(picky + p - bsearch(&delicious[i], picky, p, sizeof(int), cmp));
        int poor_can_eat = (int)(bsearch(&price[i], poor, q, sizeof(int), cmp) - poor);

        can_eat_count += picky_can_eat + poor_can_eat;
        can_eat[i] = can_eat_count;

        if (can_eat_count > 0) {
            total_can_eat++;
        }
    }

    if (total_can_eat < m) {
        printf("-1\n");
    } else {
        int max_weeks = 0;
        for (int i = 0; i < m; i++) {
            int weeks = (can_eat[i] + n - 1) / n;
            if (weeks > max_weeks) {
                max_weeks = weeks;
            }
        }
        printf("%d\n", max_weeks);
    }

    return 0;
}