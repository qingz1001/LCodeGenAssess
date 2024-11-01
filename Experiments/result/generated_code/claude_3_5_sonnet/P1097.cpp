#include <stdio.h>
#include <stdlib.h>

#define MAX_UNIQUE 10000

typedef struct {
    int number;
    int count;
} NumberCount;

int compare(const void *a, const void *b) {
    return ((NumberCount*)a)->number - ((NumberCount*)b)->number;
}

int main() {
    int n, i, num, unique_count = 0;
    NumberCount numbers[MAX_UNIQUE];

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &num);

        int j;
        for (j = 0; j < unique_count; j++) {
            if (numbers[j].number == num) {
                numbers[j].count++;
                break;
            }
        }

        if (j == unique_count) {
            numbers[unique_count].number = num;
            numbers[unique_count].count = 1;
            unique_count++;
        }
    }

    qsort(numbers, unique_count, sizeof(NumberCount), compare);

    for (i = 0; i < unique_count; i++) {
        printf("%d %d\n", numbers[i].number, numbers[i].count);
    }

    return 0;
}