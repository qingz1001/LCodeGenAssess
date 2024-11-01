#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    char matrix[150][150];

    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }

    int count = 0;

    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < n; y1++) {
            if (matrix[x1][y1] == 'W') {
                for (int x2 = x1; x2 < n; x2++) {
                    for (int y2 = y1; y2 < n; y2++) {
                        int valid = 1;
                        for (int x = x1; x <= x2; x++) {
                            for (int y = y1; y <= y2; y++) {
                                if (matrix[x][y] == 'B') {
                                    valid = 0;
                                    break;
                                }
                            }
                            if (!valid) break;
                        }
                        if (valid) count++;
                    }
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}