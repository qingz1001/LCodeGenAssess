#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void assignBooks(int books[], int n, int k) {
    qsort(books, n, sizeof(int), compare);

    int start = 0;
    for (int i = 0; i < k; i++) {
        int end = start + n / k - 1;
        if (i == k - 1) {
            end = n - 1;
        }
        printf("%d %d\n", start + 1, end + 1);
        start = end + 1;
    }
}

int main() {
    int m, k;
    scanf("%d %d", &m, &k);
    int books[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &books[i]);
    }

    assignBooks(books, m, k);

    return 0;
}