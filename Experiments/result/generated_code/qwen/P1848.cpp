#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_L 1000000000

typedef struct {
    int height;
    int width;
} Book;

int compare(const void *a, const void *b) {
    return ((Book *)b)->width - ((Book *)a)->width;
}

long long minShelfHeight(int N, int L, Book books[]) {
    qsort(books, N, sizeof(Book), compare);

    long long totalHeight = 0;
    int currentWidth = 0;
    int maxHeight = 0;

    for (int i = 0; i < N; i++) {
        if (currentWidth + books[i].width > L) {
            totalHeight += maxHeight;
            currentWidth = 0;
            maxHeight = 0;
        }
        currentWidth += books[i].width;
        maxHeight = (maxHeight > books[i].height) ? maxHeight : books[i].height;
    }

    totalHeight += maxHeight;
    return totalHeight;
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);

    Book books[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    printf("%lld\n", minShelfHeight(N, L, books));

    return 0;
}