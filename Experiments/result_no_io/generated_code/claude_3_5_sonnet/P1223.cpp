#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, i;
    int time[MAX_N];
    long long total_wait = 0;
    double avg_wait;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &time[i]);
    }

    qsort(time, n, sizeof(int), compare);

    for (i = 0; i < n; i++) {
        printf("%d ", time[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        total_wait += (long long)time[i] * (n - i - 1);
    }

    avg_wait = (double)total_wait / n;

    printf("%.2f\n", avg_wait);

    return 0;
}