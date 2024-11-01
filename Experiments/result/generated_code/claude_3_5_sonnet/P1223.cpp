#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int time;
    int index;
} Person;

int compare(const void *a, const void *b) {
    return ((Person*)a)->time - ((Person*)b)->time;
}

int main() {
    int n;
    Person people[MAX_N];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &people[i].time);
        people[i].index = i + 1;
    }
    
    qsort(people, n, sizeof(Person), compare);
    
    long long total_wait = 0;
    long long cumulative_time = 0;
    
    for (int i = 0; i < n; i++) {
        printf("%d ", people[i].index);
        total_wait += cumulative_time;
        cumulative_time += people[i].time;
    }
    printf("\n");
    
    double average_wait = (double)total_wait / n;
    printf("%.2f\n", average_wait);
    
    return 0;
}