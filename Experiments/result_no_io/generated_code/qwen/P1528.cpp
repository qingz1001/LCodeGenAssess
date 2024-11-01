#include <stdio.h>
#include <stdlib.h>

#define MAX_CAKES 50
#define MAX_PEOPLE 1024

int main() {
    int cakes[MAX_CAKES];
    int people[MAX_PEOPLE];
    int n, m;
    int i, j;

    // Read input
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%d", &people[i]);
    }

    // Sort the cakes and people arrays
    qsort(cakes, n, sizeof(int), (void (*)(const void *, const void *))strcmp);
    qsort(people, m, sizeof(int), (void (*)(const void *, const void *))strcmp);

    int max_filled = 0;
    int cake_index = 0;
    int person_index = 0;

    // Try to fill each person with the smallest available cake that is large enough
    while (cake_index < n && person_index < m) {
        if (cakes[cake_index] >= people[person_index]) {
            max_filled++;
            person_index++;
        }
        cake_index++;
    }

    // Output the result
    printf("%d\n", max_filled);

    return 0;
}