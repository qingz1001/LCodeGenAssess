#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findClosest(int *schools, int m, int score) {
    int left = 0, right = m - 1;
    int closest = INT_MAX;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (abs(schools[mid] - score) < abs(closest - score)) {
            closest = schools[mid];
        }
        if (schools[mid] == score) {
            return schools[mid];
        } else if (schools[mid] < score) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return closest;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int *schools = (int *)malloc(m * sizeof(int));
    int *students = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++) {
        scanf("%d", &schools[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }

    qsort(schools, m, sizeof(int), compare);

    long long dissatisfaction = 0;

    for (int i = 0; i < n; i++) {
        int closest = findClosest(schools, m, students[i]);
        dissatisfaction += abs(closest - students[i]);
    }

    printf("%lld\n", dissatisfaction);

    free(schools);
    free(students);

    return 0;
}