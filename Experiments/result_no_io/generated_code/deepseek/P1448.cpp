#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

int N, M;
int scarf[MAXN][MAXN * 2];

int max(int a, int b) {
    return a > b ? a : b;
}

int is_valid(int x, int y, int size) {
    if (x + size > N || y + size * 2 - 2 > 2 * N - 1) return 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            if (scarf[x + i][y + j]) return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &N, &M);
    memset(scarf, 0, sizeof(scarf));

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        scarf[x - 1][y - 1] = 1;
    }

    int max_area = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2 * N - 1; j++) {
            if (scarf[i][j]) continue;
            int max_size = 1;
            while (is_valid(i, j, max_size + 1)) {
                max_size++;
            }
            int area1 = max_size * max_size;

            for (int k = i + max_size; k < N; k++) {
                for (int l = 0; l < 2 * N - 1; l++) {
                    if (scarf[k][l]) continue;
                    int max_size2 = 1;
                    while (is_valid(k, l, max_size2 + 1)) {
                        max_size2++;
                    }
                    int area2 = max_size2 * max_size2;
                    max_area = max(max_area, area1 + area2);
                }
            }
        }
    }

    printf("%d\n", max_area);
    return 0;
}