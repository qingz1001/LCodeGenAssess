#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    int count;
} NumberCount;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compareNumberCount(const void *a, const void *b) {
    return ((NumberCount *)a)->number - ((NumberCount *)b)->number;
}

int main() {
    int n;
    scanf("%d", &n);
    int *numbers = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    qsort(numbers, n, sizeof(int), compare);

    NumberCount *result = (NumberCount *)malloc(n * sizeof(NumberCount));
    int resultSize = 0;

    for (int i = 0; i < n; i++) {
        if (i == 0 || numbers[i] != numbers[i - 1]) {
            result[resultSize].number = numbers[i];
            result[resultSize].count = 1;
            resultSize++;
        } else {
            result[resultSize - 1].count++;
        }
    }

    qsort(result, resultSize, sizeof(NumberCount), compareNumberCount);

    for (int i = 0; i < resultSize; i++) {
        printf("%d %d\n", result[i].number, result[i].count);
    }

    free(numbers);
    free(result);

    return 0;
}