#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int index;
} Person;

int compare(const void *a, const void *b) {
    return ((Person *)a)->time - ((Person *)b)->time;
}

int main() {
    int n;
    scanf("%d", &n);
    Person people[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &people[i].time);
        people[i].index = i + 1;
    }

    qsort(people, n, sizeof(Person), compare);

    for (int i = 0; i < n; i++) {
        printf("%d ", people[i].index);
    }
    printf("\n");

    double total_wait_time = 0;
    double current_wait_time = 0;
    for (int i = 0; i < n; i++) {
        total_wait_time += current_wait_time;
        current_wait_time += people[i].time;
    }

    printf("%.2f\n", total_wait_time / n);

    return 0;
}