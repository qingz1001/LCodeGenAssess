#include <stdio.h>
#include <stdlib.h>

#define MAX_R 205
#define MAX_C 500005

int books[MAX_R][MAX_C];
int prefixSum[MAX_R][MAX_C];
int sortedBooks[MAX_C];
int sortedPrefixSum[MAX_C];

void initializePrefixSum(int R, int C) {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            prefixSum[i][j] = prefixSum[i][j-1] + books[i][j];
        }
    }
}

void initializeSortedBooks(int C) {
    for (int j = 1; j <= C; j++) {
        sortedBooks[j] = books[1][j];
    }
    for (int i = 2; i <= MAX_R; i++) {
        for (int j = 1; j <= C; j++) {
            sortedBooks[j] += books[i][j];
        }
    }
    qsort(sortedBooks + 1, C, sizeof(int), cmp);
    for (int j = 1; j <= C; j++) {
        sortedPrefixSum[j] = sortedPrefixSum[j-1] + sortedBooks[j];
    }
}

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    int R, C, M;
    scanf("%d %d %d", &R, &C, &M);

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &books[i][j]);
        }
    }

    initializePrefixSum(R, C);
    initializeSortedBooks(C);

    for (int i = 0; i < M; i++) {
        int x1, y1, x2, y2, H;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &H);

        int totalBooks = (x2 - x1 + 1) * (y2 - y1 + 1);
        int totalPages = prefixSum[x2][y2] - prefixSum[x2][y1 - 1] - prefixSum[x1 - 1][y2] + prefixSum[x1 - 1][y1 - 1];

        if (totalPages < H) {
            printf("Poor QLW\n");
            continue;
        }

        int low = 1, high = C;
        while (low < high) {
            int mid = (low + high) / 2;
            if (sortedPrefixSum[mid] >= H) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        if (sortedPrefixSum[low] < H) {
            printf("Poor QLW\n");
        } else {
            printf("%d\n", low);
        }
    }

    return 0;
}