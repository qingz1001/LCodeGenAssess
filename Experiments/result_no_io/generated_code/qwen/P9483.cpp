#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef struct {
    int weight;
    int wear;
} Book;

int compare(const void *a, const void *b) {
    return ((Book *)a)->weight - ((Book *)b)->weight;
}

long long mergeBooks(Book books[], int n) {
    qsort(books, n, sizeof(Book), compare);

    long long minCost = 0;
    while (n > 1) {
        Book merged;
        merged.weight = books[0].weight + books[1].weight;
        merged.wear = 2 * (books[0].wear > books[1].wear ? books[0].wear : books[1].wear) + 1;

        minCost += merged.weight + merged.wear;

        for (int i = 1; i < n; i++) {
            books[i - 1] = books[i];
        }
        books[n - 2] = merged;
        n--;
    }

    return minCost;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        Book books[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%d", &books[i].weight);
            books[i].wear = 0;
        }

        printf("%lld\n", mergeBooks(books, n));
    }
    return 0;
}