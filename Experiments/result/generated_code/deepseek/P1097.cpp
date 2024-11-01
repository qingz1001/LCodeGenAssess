#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    int count;
} NumberCount;

int compare(const void *a, const void *b) {
    return ((NumberCount *)a)->number - ((NumberCount *)b)->number;
}

int main() {
    int n;
    scanf("%d", &n);

    NumberCount *numbers = (NumberCount *)malloc(n * sizeof(NumberCount));
    int uniqueCount = 0;

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);

        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (numbers[j].number == num) {
                numbers[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            numbers[uniqueCount].number = num;
            numbers[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    qsort(numbers, uniqueCount, sizeof(NumberCount), compare);

    for (int i = 0; i < uniqueCount; i++) {
        printf("%d %d\n", numbers[i].number, numbers[i].count);
    }

    free(numbers);
    return 0;
}