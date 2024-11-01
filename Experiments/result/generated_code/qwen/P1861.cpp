#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int n, m;
int ini[MAX_N][MAX_M];
int fin[MAX_N][MAX_M];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int calculate_magic(int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) {
        return abs(x1 - x2) + abs(y1 - y2) - 1;
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &ini[i][j]);
        }
    }

    getchar(); // Consume the newline character

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &fin[i][j]);
        }
    }

    int magic = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int diff = fin[i][j] - ini[i][j];
            if (diff > 0) {
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < m; l++) {
                        if (k != i && l != j && ini[k][l] >= diff) {
                            ini[k][l] -= diff;
                            ini[i][j] += diff;
                            magic += calculate_magic(i, j, k, l);
                            break;
                        }
                    }
                    if (ini[i][j] >= diff) break;
                }
            } else if (diff < 0) {
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < m; l++) {
                        if (k != i && l != j && ini[k][l] <= -diff) {
                            ini[k][l] += -diff;
                            ini[i][j] += -diff;
                            magic += calculate_magic(i, j, k, l);
                            break;
                        }
                    }
                    if (ini[i][j] <= -diff) break;
                }
            }
        }
    }

    printf("%d\n", magic);

    return 0;
}