#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int thickness;
} Book;

int compare(const void *a, const void *b) {
    Book *bookA = (Book *)a;
    Book *bookB = (Book *)b;
    if (bookA->thickness == bookB->thickness) {
        return bookA->height - bookB->height;
    }
    return bookA->thickness - bookB->thickness;
}

int main() {
    int n;
    scanf("%d", &n);
    Book books[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].height, &books[i].thickness);
    }

    qsort(books, n, sizeof(Book), compare);

    int sumThickness[4][4] = {0};
    int maxThickness[4] = {0};
    int maxHeight[4] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 3; j++) {
            for (int k = 1; k <= 3; k++) {
                if (sumThickness[j][k] + books[i].thickness <= maxThickness[k]) {
                    sumThickness[j][k] += books[i].thickness;
                    maxThickness[k] = sumThickness[j][k];
                    maxHeight[j] = books[i].height;
                }
            }
        }
    }

    int minSurfaceArea = INT_MAX;
    for (int j = 1; j <= 3; j++) {
        for (int k = 1; k <= 3; k++) {
            if (j != k) {
                int surfaceArea = (maxHeight[j] + maxHeight[k]) * maxThickness[j];
                if (surfaceArea < minSurfaceArea) {
                    minSurfaceArea = surfaceArea;
                }
            }
        }
    }

    printf("%d\n", minSurfaceArea);
    return 0;
}