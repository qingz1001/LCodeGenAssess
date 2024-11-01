#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100

typedef struct {
    int height;
    int width;
} Book;

int compare(const void *a, const void *b) {
    return ((Book *)a)->height - ((Book *)b)->height;
}

int main() {
    int n, k;
    Book books[MAX_N];
    
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }
    
    qsort(books, n, sizeof(Book), compare);
    
    int min_messiness = 1e9;
    
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k - i; j++) {
            int messiness = 0;
            for (int l = i + 1; l < n - j; l++) {
                messiness += abs(books[l].width - books[l-1].width);
            }
            if (messiness < min_messiness) {
                min_messiness = messiness;
            }
        }
    }
    
    printf("%d\n", min_messiness);
    
    return 0;
}