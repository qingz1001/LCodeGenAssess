#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

int city[MAX_N][MAX_M];
int bombCount[MAX_N][MAX_M];
int lastBomb[MAX_N][MAX_M];

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    memset(city, 0, sizeof(city));
    memset(bombCount, 0, sizeof(bombCount));
    memset(lastBomb, 0, sizeof(lastBomb));

    for (int i = 1; i <= x; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;  // 调整为0-based索引

        for (int r = x1; r <= x2; r++) {
            for (int c = y1; c <= y2; c++) {
                city[r][c] = 1;
                bombCount[r][c]++;
                lastBomb[r][c] = i;
            }
        }
    }

    for (int i = 0; i < y; i++) {
        int px, py;
        scanf("%d %d", &px, &py);
        px--; py--;  // 调整为0-based索引

        if (city[px][py]) {
            printf("Y %d %d\n", bombCount[px][py], lastBomb[px][py]);
        } else {
            printf("N\n");
        }
    }

    return 0;
}