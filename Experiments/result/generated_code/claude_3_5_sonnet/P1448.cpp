#include <stdio.h>
#include <string.h>

#define MAX_N 101
#define MAX_M 10001

int N, M;
int damaged[MAX_N][2*MAX_N];
int dp[MAX_N][MAX_N][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int getArea(int size) {
    return size * (size + 1) / 2;
}

int isValid(int x, int y, int size) {
    if (x + size - 1 > N || y + size - 1 > 2*x-1) return 0;
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size + i - x; j++) {
            if (damaged[i][j]) return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &N);
    scanf("%d", &M);

    memset(damaged, 0, sizeof(damaged));
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        damaged[x][y] = 1;
    }

    memset(dp, -1, sizeof(dp));

    int maxArea = 0;
    for (int size1 = N; size1 >= 1; size1--) {
        for (int x1 = 1; x1 <= N - size1 + 1; x1++) {
            for (int y1 = 1; y1 <= 2*x1-1; y1++) {
                if (!isValid(x1, y1, size1)) continue;

                for (int size2 = N; size2 >= 1; size2--) {
                    for (int x2 = 1; x2 <= N - size2 + 1; x2++) {
                        for (int y2 = 1; y2 <= 2*x2-1; y2++) {
                            if (!isValid(x2, y2, size2)) continue;

                            int area = getArea(size1) + getArea(size2);
                            if (area > maxArea) {
                                maxArea = area;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", maxArea);
    return 0;
}