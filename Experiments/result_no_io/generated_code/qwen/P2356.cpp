#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int main() {
    int n;
    scanf("%d", &n);
    int enemies[MAXN][MAXN];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &enemies[i][j]);
        }
    }

    int max_score = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (enemies[i][j] == 0) {
                int score = 0;
                for (int k = 0; k < n; ++k) {
                    score += enemies[i][k];
                    score += enemies[k][j];
                }
                if (max_score == -1 || score > max_score) {
                    max_score = score;
                }
            }
        }
    }

    if (max_score == -1) {
        printf("Bad Game!\n");
    } else {
        printf("%d\n", max_score);
    }

    return 0;
}