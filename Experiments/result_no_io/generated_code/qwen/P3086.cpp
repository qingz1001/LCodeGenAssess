#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300

int main() {
    int N;
    scanf("%d", &N);

    char grid[MAX_N][MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%s", grid[i]);
    }

    int max_score = -1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == '*') continue;

            // Find the top rectangle
            int top_area = 0;
            for (int k = i; k >= 0; --k) {
                if (grid[k][j] == '*') break;
                for (int l = j; l < N && grid[k][l] != '*'; ++l) {
                    top_area++;
                }
            }

            // Find the bottom rectangle
            int bottom_area = 0;
            for (int k = i; k < N; ++k) {
                if (grid[k][j] == '*') break;
                for (int l = j; l >= 0 && grid[k][l] != '*'; --l) {
                    bottom_area++;
                }
            }

            // Calculate the score
            if (top_area > 0 && bottom_area > 0) {
                int score = top_area * bottom_area;
                if (score > max_score) {
                    max_score = score;
                }
            }
        }
    }

    printf("%d\n", max_score);
    return 0;
}