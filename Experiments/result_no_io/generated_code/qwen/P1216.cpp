#include <stdio.h>

#define MAXN 1000

int main() {
    int r;
    scanf("%d", &r);
    
    int triangle[MAXN][MAXN];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j <= i; ++j) {
            scanf("%d", &triangle[i][j]);
        }
    }

    for (int i = r - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] += (triangle[i + 1][j] > triangle[i + 1][j + 1]) ? triangle[i + 1][j] : triangle[i + 1][j + 1];
        }
    }

    printf("%d\n", triangle[0][0]);

    return 0;
}