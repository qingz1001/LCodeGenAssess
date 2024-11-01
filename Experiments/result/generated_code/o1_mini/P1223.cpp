#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    long long time;
} Person;

// Comparator function for qsort
int cmp(const void *a, const void *b){
    if(((Person*)a)->time < ((Person*)b)->time) return -1;
    if(((Person*)a)->time > ((Person*)b)->time) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Person people[n];
    for(int i=0; i<n; i++){
        scanf("%lld", &people[i].time);
        people[i].index = i+1;
    }
    qsort(people, n, sizeof(Person), cmp);
    // Print sorted indices
    for(int i=0; i<n; i++){
        printf("%d", people[i].index);
        if(i != n-1) printf(" ");
    }
    printf("\n");
    // Calculate average waiting time
    long long total = 0;
    long long cumulative = 0;
    for(int i=0; i<n; i++){
        cumulative += people[i].time;
        total += cumulative;
    }
    double average = (double)total / n;
    printf("%.2lf\n", average);
    return 0;
}