#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

typedef struct {
    int a;
    int b;
    int rank;
} Person;

int cmp(const void *a, const void *b) {
    Person *pa = (Person *)a;
    Person *pb = (Person *)b;
    return pb->a - pa->a;
}

int main() {
    int n;
    Person people[MAX_N];
    int count[MAX_N] = {0};
    int liars = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &people[i].a, &people[i].b);
        people[i].rank = i;
    }

    qsort(people, n, sizeof(Person), cmp);

    for (int i = 0; i < n; i++) {
        int rank = n - i - 1;
        if (people[i].a != i || people[i].b != rank) {
            liars++;
        }
        count[people[i].rank] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        if (count[i] != people[i].a + 1) {
            liars++;
        }
    }

    printf("%d\n", liars / 2);

    return 0;
}