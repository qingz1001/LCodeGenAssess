#include <stdio.h>
#include <stdlib.h>

#define MAX_R 200
#define MAX_C 500000
#define MAX_M 200000

int R, C, M;
int P[MAX_R][MAX_C];
int prefixSum[MAX_R][MAX_C];

void calculatePrefixSum() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            prefixSum[i][j] = P[i][j] + prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1];
        }
    }
}

int getSum(int x1, int y1, int x2, int y2) {
    return prefixSum[x2][y2] - prefixSum[x1-1][y2] - prefixSum[x2][y1-1] + prefixSum[x1-1][y1-1];
}

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main() {
    scanf("%d %d %d", &R, &C, &M);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &P[i][j]);
        }
    }

    calculatePrefixSum();

    for (int q = 0; q < M; q++) {
        int x1, y1, x2, y2, H;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &H);

        int totalSum = getSum(x1, y1, x2, y2);
        if (totalSum < H) {
            printf("Poor QLW\n");
            continue;
        }

        int books[MAX_R * MAX_C];
        int idx = 0;
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                books[idx++] = P[i][j];
            }
        }

        qsort(books, idx, sizeof(int), compare);

        int sum = 0;
        int count = 0;
        for (int i = 0; i < idx; i++) {
            sum += books[i];
            count++;
            if (sum >= H) {
                printf("%d\n", count);
                break;
            }
        }
    }

    return 0;
}