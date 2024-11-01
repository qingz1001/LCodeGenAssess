#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 1000
#define MAX_K 1000

int n, m, k;
int schedule[MAX_N][MAX_M];
int contest_count[MAX_K + 1];

int main() {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &schedule[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int day = schedule[i][j];
            if (contest_count[day] == j) {
                contest_count[day]++;
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        printf("%d ", contest_count[i]);
    }

    return 0;
}