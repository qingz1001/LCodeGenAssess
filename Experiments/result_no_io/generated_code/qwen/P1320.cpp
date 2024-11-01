#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    char grid[N][N];
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }

    printf("%d ", N);
    int count = 0, prev = grid[0][0] - '0';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] - '0' != prev) {
                printf("%d ", count);
                count = 1;
                prev = grid[i][j] - '0';
            } else {
                count++;
            }
        }
    }
    printf("%d\n", count);

    return 0;
}