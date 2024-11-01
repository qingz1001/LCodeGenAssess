#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXL 1000000000

typedef struct {
    int height;
    int width;
} Book;

int compare(const void *a, const void *b) {
    return ((Book *)b)->width - ((Book *)a)->width;
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);
    Book books[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    qsort(books, N, sizeof(Book), compare);

    long long minHeight = 0;
    int currentWidth = 0;
    int maxHeightOnCurrentShelf = 0;

    for (int i = 0; i < N; i++) {
        if (currentWidth + books[i].width > L) {
            minHeight += maxHeightOnCurrentShelf;
            currentWidth = 0;
            maxHeightOnCurrentShelf = 0;
        }
        currentWidth += books[i].width;
        maxHeightOnCurrentShelf = books[i].height;
    }
    minHeight += maxHeightOnCurrentShelf;

    printf("%lld\n", minHeight);

    return 0;
}