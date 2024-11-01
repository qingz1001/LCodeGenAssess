#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int Ini[MAX_N][MAX_M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &Ini[i][j]);
        }
    }

    // Skip the empty line
    getchar();

    int Fin[MAX_N][MAX_M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &Fin[i][j]);
        }
    }

    int max_magic = 0;

    // Check rows
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M - 1; j++) {
            if (Ini[i][j] > 0 && Ini[i][j + 1] > 0) {
                int move = Ini[i][j] + Ini[i][j + 1];
                if (move <= Fin[i][j] + Fin[i][j + 1]) {
                    max_magic += abs(Fin[i][j] - Ini[i][j]) + abs(Fin[i][j + 1] - Ini[i][j + 1]);
                } else {
                    int diff = move - (Fin[i][j] + Fin[i][j + 1]);
                    max_magic += abs(Fin[i][j] - Ini[i][j]) + abs(Fin[i][j + 1] - Ini[i][j + 1]);
                    Ini[i][j] -= diff / 2;
                    Ini[i][j + 1] -= diff / 2;
                }
            }
        }
    }

    // Check columns
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N - 1; i++) {
            if (Ini[i][j] > 0 && Ini[i + 1][j] > 0) {
                int move = Ini[i][j] + Ini[i + 1][j];
                if (move <= Fin[i][j] + Fin[i + 1][j]) {
                    max_magic += abs(Fin[i][j] - Ini[i][j]) + abs(Fin[i + 1][j] - Ini[i + 1][j]);
                } else {
                    int diff = move - (Fin[i][j] + Fin[i + 1][j]);
                    max_magic += abs(Fin[i][j] - Ini[i][j]) + abs(Fin[i + 1][j] - Ini[i + 1][j]);
                    Ini[i][j] -= diff / 2;
                    Ini[i + 1][j] -= diff / 2;
                }
            }
        }
    }

    printf("%d\n", max_magic);
    return 0;
}