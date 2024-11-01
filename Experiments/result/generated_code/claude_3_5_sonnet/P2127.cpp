#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int value;
    int index;
} Number;

int compare(const void* a, const void* b) {
    return ((Number*)a)->value - ((Number*)b)->value;
}

int main() {
    int N;
    scanf("%d", &N);

    Number numbers[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i].value);
        numbers[i].index = i;
    }

    qsort(numbers, N, sizeof(Number), compare);

    long long cost = 0;
    for (int i = 0; i < N; i++) {
        if (numbers[i].index != i) {
            cost += numbers[i].value + numbers[numbers[i].index].value;
            int temp = numbers[i].index;
            numbers[i].index = numbers[temp].index;
            numbers[temp].index = temp;
        }
    }

    printf("%lld\n", cost);

    return 0;
}