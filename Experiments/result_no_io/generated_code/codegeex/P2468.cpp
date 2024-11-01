#include <stdio.h>
#include <stdlib.h>

#define MAX_R 201
#define MAX_C 201
#define MAX_M 200001

int R, C, M;
int P[MAX_R][MAX_C];
int x1[MAX_M], y1[MAX_M], x2[MAX_M], y2[MAX_M], H[MAX_M];

void read_input() {
    scanf("%d %d %d", &R, &C, &M);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i], &H[i]);
    }
}

int main() {
    read_input();

    for (int i = 0; i < M; i++) {
        int cnt = 0;
        int sum = 0;
        for (int j = x1[i]; j <= x2[i]; j++) {
            for (int k = y1[i]; k <= y2[i]; k++) {
                if (P[j][k] > H[i]) {
                    cnt++;
                    sum += P[j][k];
                    if (sum >= H[i]) {
                        printf("%d\n", cnt);
                        goto next;
                    }
                }
            }
        }
        printf("Poor QLW\n");
        next:;
    }

    return 0;
}