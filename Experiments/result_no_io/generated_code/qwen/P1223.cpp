#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

double calculate_average_wait_time(int *times, int n) {
    double total_wait_time = 0;
    for (int i = 0; i < n; i++) {
        total_wait_time += times[i] * (n - i);
    }
    return total_wait_time / n;
}

int main() {
    int n;
    scanf("%d", &n);

    int times[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &times[i]);
    }

    qsort(times, n, sizeof(int), compare);

    printf("Sorted order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", times[i]);
    }
    printf("\n");

    double average_wait_time = calculate_average_wait_time(times, n);
    printf("%.2f\n", average_wait_time);

    return 0;
}