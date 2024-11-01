#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50005
#define MAX_XY 1003

int main() {
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);

    int hay[MAX_N][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &hay[i][0], &hay[i][1]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (hay[i][0] == x0 || hay[i][1] == y0) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}