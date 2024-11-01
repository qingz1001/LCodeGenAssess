#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
#define MAX_M 1001

int n, m;
int stations[MAX_N];
int stops[MAX_M][MAX_N];
int stop_count[MAX_M];

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d", &stop_count[i]);
        for (int j = 0; j < stop_count[i]; j++) {
            scanf("%d", &stops[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        stations[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int max_level = 1;
        for (int j = 0; j < stop_count[i]; j++) {
            if (stations[stops[i][j]] > max_level) {
                max_level = stations[stops[i][j]];
            }
        }
        for (int j = stops[i][0]; j <= stops[i][stop_count[i]-1]; j++) {
            if (stations[j] < max_level) {
                stations[j] = max_level;
            }
        }
        for (int j = 0; j < stop_count[i]; j++) {
            if (stations[stops[i][j]] == max_level) {
                stations[stops[i][j]]++;
            }
        }
    }

    qsort(stations + 1, n, sizeof(int), compare);

    int levels = 1;
    for (int i = 2; i <= n; i++) {
        if (stations[i] != stations[i-1]) {
            levels++;
        }
    }

    printf("%d\n", levels);

    return 0;
}