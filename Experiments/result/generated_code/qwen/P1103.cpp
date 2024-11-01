#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int *pairA = (int *)a;
    int *pairB = (int *)b;
    if (pairA[0] != pairB[0]) return pairA[0] - pairB[0];
    else return pairA[1] - pairB[1];
}

int minUnsortedness(int n, int k, int books[][2]) {
    for (int i = 0; i < n; i++) {
        books[i][1] -= books[i][0];
    }
    qsort(books, n, sizeof(int) * 2, compare);

    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        sum += abs(books[i + 1][1] - books[i][1]);
    }

    for (int i = 0; i < k; i++) {
        sum -= abs(books[i + 1][1] - books[i][1]);
        sum += abs(books[n - 1 - i + 1][1] - books[n - 1 - i][1]);
    }

    return sum;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int books[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i][0], &books[i][1]);
    }

    printf("%d\n", minUnsortedness(n, k, books));

    return 0;
}