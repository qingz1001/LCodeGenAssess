#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Number;

int compare(const void *a, const void *b) {
    return ((Number*)b)->value - ((Number*)a)->value;
}

int main() {
    Number numbers[8];
    for (int i = 0; i < 8; i++) {
        scanf("%d", &numbers[i].value);
        numbers[i].index = i + 1;
    }

    qsort(numbers, 8, sizeof(Number), compare);

    int sum = 0;
    int indices[5];
    for (int i = 0; i < 5; i++) {
        sum += numbers[i].value;
        indices[i] = numbers[i].index;
    }

    qsort(indices, 5, sizeof(int), compare);

    printf("%d\n", sum);
    for (int i = 4; i >= 0; i--) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    return 0;
}