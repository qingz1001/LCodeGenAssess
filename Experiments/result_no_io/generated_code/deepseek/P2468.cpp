#include <stdio.h>
#include <stdlib.h>

#define MAX_R 200
#define MAX_C 500000
#define MAX_M 200000

int R, C, M;
int P[MAX_R + 1][MAX_C + 1];
int x1[MAX_M], y1[MAX_M], x2[MAX_M], y2[MAX_M], H[MAX_M];

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

void solve() {
    for (int i = 0; i < M; i++) {
        int x1i = x1[i], y1i = y1[i], x2i = x2[i], y2i = y2[i], Hi = H[i];
        int books[MAX_R * MAX_C];
        int count = 0;

        for (int x = x1i; x <= x2i; x++) {
            for (int y = y1i; y <= y2i; y++) {
                books[count++] = P[x][y];
            }
        }

        qsort(books, count, sizeof(int), compare);

        int sum = 0;
        int num_books = 0;
        for (int j = 0; j < count; j++) {
            sum += books[j];
            num_books++;
            if (sum >= Hi) {
                printf("%d\n", num_books);
                break;
            }
        }

        if (sum < Hi) {
            printf("Poor QLW\n");
        }
    }
}

int main() {
    scanf("%d %d %d", &R, &C, &M);

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &P[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i], &H[i]);
    }

    solve();

    return 0;
}