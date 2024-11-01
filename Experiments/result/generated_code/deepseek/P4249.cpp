#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int N;
int matrix[MAXN][MAXN];
int result[MAXN][MAXN];

void read_input() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void solve() {
    int scissors_rock_paper_count = 0;

    // Copy the input matrix to result matrix and replace 2 with 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 2) {
                result[i][j] = 0;
            } else {
                result[i][j] = matrix[i][j];
            }
        }
    }

    // Count the number of scissors-rock-paper situations
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if ((result[i][j] == 1 && result[j][k] == 1 && result[k][i] == 1) ||
                    (result[i][j] == 0 && result[j][k] == 0 && result[k][i] == 0)) {
                    scissors_rock_paper_count++;
                }
            }
        }
    }

    // Output the result
    printf("%d\n", scissors_rock_paper_count);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

int main() {
    read_input();
    solve();
    return 0;
}