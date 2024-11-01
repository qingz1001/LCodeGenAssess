#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int width;
} Book;

int compare(const void *a, const void *b) {
    Book *bookA = (Book *)a;
    Book *bookB = (Book *)b;
    return bookA->height - bookB->height;
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);
    
    Book books[N];
    int totalWidth = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
        totalWidth += books[i].width;
    }
    
    qsort(books, N, sizeof(Book), compare);
    
    int *dp = (int *)malloc(sizeof(int) * (totalWidth + 1));
    for (int i = 0; i <= totalWidth; i++) {
        dp[i] = 0;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = totalWidth; j >= 0; j--) {
            if (j + books[i].width <= L) {
                dp[j + books[i].width] = (dp[j + books[i].width] > dp[j] + books[i].height) ? dp[j + books[i].width] : dp[j] + books[i].height;
            }
        }
    }
    
    int min_height = dp[totalWidth];
    free(dp);
    
    printf("%d\n", min_height);
    return 0;
}