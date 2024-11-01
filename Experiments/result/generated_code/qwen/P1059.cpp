#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 1000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    scanf("%d", &N);
    int numbers[MAX_NUM];
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }

    qsort(numbers, N, sizeof(int), compare);

    int unique_count = 1;
    for (int i = 1; i < N; i++) {
        if (numbers[i] != numbers[i - 1]) {
            numbers[unique_count++] = numbers[i];
        }
    }

    printf("%d\n", unique_count);
    for (int i = 0; i < unique_count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}