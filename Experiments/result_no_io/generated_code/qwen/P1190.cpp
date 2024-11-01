#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int water;
    int time;
} Student;

int compare(const void *a, const void *b) {
    return ((Student *)b)->water - ((Student *)a)->water;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Student students[n];
    for (int i = 0; i < n; ++i) {
        students[i].id = i + 1;
        scanf("%d", &students[i].water);
        students[i].time = 0;
    }

    qsort(students, n, sizeof(Student), compare);

    int times[m];
    for (int i = 0; i < m; ++i) {
        times[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        int min_time = times[0];
        int min_index = 0;
        for (int j = 1; j < m; ++j) {
            if (times[j] < min_time) {
                min_time = times[j];
                min_index = j;
            }
        }
        times[min_index] += students[i].water;
        students[i].time = times[min_index];
    }

    int max_time = 0;
    for (int i = 0; i < m; ++i) {
        if (times[i] > max_time) {
            max_time = times[i];
        }
    }

    printf("%d\n", max_time);

    return 0;
}