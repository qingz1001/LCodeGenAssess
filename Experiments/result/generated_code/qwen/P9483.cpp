#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int wear;
} Book;

int compare(const void *a, const void *b) {
    return ((Book *)a)->weight - ((Book *)b)->weight;
}

long long mergeBooks(int n, Book books[]) {
    qsort(books, n, sizeof(Book), compare);

    for (int i = 1; i < n; i++) {
        books[i].wear = books[i - 1].wear * 2 + 1;
        books[i].weight += books[i - 1].weight;
    }

    long long minEffort = 0;
    for (int i = 1; i < n; i++) {
        minEffort += books[i].weight + books[i].wear;
    }

    return minEffort;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        Book books[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &books[i].weight);
            books[i].wear = 0;
        }
        printf("%lld\n", mergeBooks(n, books));
    }
    return 0;
}