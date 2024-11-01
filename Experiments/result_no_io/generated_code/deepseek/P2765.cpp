#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_N 55
#define MAX_BALLS 1000

bool isPerfectSquare(int x) {
    int s = (int)sqrt(x);
    return s * s == x;
}

int main() {
    int n;
    scanf("%d", &n);

    int balls[MAX_N][MAX_BALLS] = {0};
    int top[MAX_N] = {0};
    int totalBalls = 0;

    for (int i = 1; ; i++) {
        bool placed = false;
        for (int j = 0; j < n; j++) {
            if (top[j] == 0 || isPerfectSquare(balls[j][top[j] - 1] + i)) {
                balls[j][top[j]++] = i;
                placed = true;
                totalBalls++;
                break;
            }
        }
        if (!placed) break;
    }

    printf("%d\n", totalBalls);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < top[i]; j++) {
            printf("%d", balls[i][j]);
            if (j < top[i] - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}