#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 1000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int stops[MAX_M][MAX_N];
    for (int i = 0; i < m; ++i) {
        int s;
        scanf("%d", &s);
        for (int j = 0; j < s; ++j) {
            scanf("%d", &stops[i][j]);
        }
    }

    int levels[MAX_N] = {0};
    for (int i = 0; i < m; ++i) {
        int max_level = 0;
        for (int j = 0; j < stops[i][0]; ++j) {
            if (stops[i][j] > max_level) {
                max_level = stops[i][j];
            }
        }
        for (int j = 0; j < stops[i][0]; ++j) {
            levels[stops[i][j]] = max_level;
        }
    }

    int min_levels = 0;
    for (int i = 1; i <= n; ++i) {
        if (levels[i] > min_levels) {
            min_levels = levels[i];
        }
    }

    printf("%d\n", min_levels);

    return 0;
}