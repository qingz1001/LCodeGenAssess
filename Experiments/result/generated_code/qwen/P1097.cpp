#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 1000000000
#define MAX_COUNT 10000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int numbers[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    qsort(numbers, n, sizeof(int), compare);

    int count[MAX_COUNT + 1] = {0};
    int current_number = numbers[0];
    int current_count = 1;

    for (int i = 1; i < n; i++) {
        if (numbers[i] == current_number) {
            current_count++;
        } else {
            printf("%d %d\n", current_number, current_count);
            current_number = numbers[i];
            current_count = 1;
        }
    }
    printf("%d %d\n", current_number, current_count);

    return 0;
}