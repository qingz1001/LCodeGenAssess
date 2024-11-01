#include <stdio.h>
#include <string.h>

int main() {
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);

    int x[n], y[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    int min_moves = n;
    for (int i = 0; i < n; i++) {
        int moves = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (x[i] == x[j] || y[i] == y[j]) {
                    moves++;
                }
            }
        }
        min_moves = (min_moves < moves) ? min_moves : moves;
    }

    printf("%d\n", min_moves);
    return 0;
}