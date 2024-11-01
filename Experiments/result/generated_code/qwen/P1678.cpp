#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int schools[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &schools[i]);
    }

    int students[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }

    qsort(schools, m, sizeof(int), compare);

    long long total dissatisfaction = 0;
    for (int i = 0; i < n; i++) {
        int diff = abs(students[i] - schools[i]);
        dissatisfaction += diff;
    }

    printf("%lld\n", total dissatisfaction);

    return 0;
}