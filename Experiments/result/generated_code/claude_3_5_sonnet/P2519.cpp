#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int a;
    int b;
} Person;

int compare(const void* a, const void* b) {
    return ((Person*)a)->a - ((Person*)b)->a;
}

int main() {
    int n;
    scanf("%d", &n);

    Person people[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &people[i].a, &people[i].b);
    }

    qsort(people, n, sizeof(Person), compare);

    int liars = 0;
    int rank = 0;
    int same_rank = 1;

    for (int i = 0; i < n; i++) {
        if (i > 0 && people[i].a != people[i-1].a) {
            rank += same_rank;
            same_rank = 1;
        } else if (i > 0) {
            same_rank++;
        }

        if (people[i].a != rank || people[i].b != n - rank - same_rank) {
            liars++;
        }
    }

    printf("%d\n", liars);

    return 0;
}