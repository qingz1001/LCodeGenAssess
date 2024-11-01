#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 100

int N, M;
bool damaged[MAXN + 1][2 * MAXN];

bool is_valid(int x, int y) {
    return x >= 1 && x <= N && y >= 1 && y <= 2 * x - 1;
}

bool is_triangle_valid(int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 2 * (i + 1) - 1; j++) {
            if (damaged[x + i][y + j]) {
                return false;
            }
        }
    }
    return true;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        damaged[x][y] = true;
    }

    int max_area = 0;

    for (int size = 1; size <= N; size++) {
        for (int x = 1; x <= N - size + 1; x++) {
            for (int y = 1; y <= 2 * x - 1; y++) {
                if (is_valid(x + size - 1, y + 2 * (size - 1)) && is_triangle_valid(x, y, size)) {
                    int area1 = size * size;
                    for (int size2 = 1; size2 <= N - size; size2++) {
                        for (int x2 = 1; x2 <= N - size2 + 1; x2++) {
                            for (int y2 = 1; y2 <= 2 * x2 - 1; y2++) {
                                if (is_valid(x2 + size2 - 1, y2 + 2 * (size2 - 1)) && is_triangle_valid(x2, y2, size2)) {
                                    max_area = max(max_area, area1 + size2 * size2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", max_area);
    return 0;
}