#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int score;
} Student;

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    if (studentA->score == studentB->score) {
        return studentA->id - studentB->id;
    }
    return studentB->score - studentA->score;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    m = m * 1.5;

    Student students[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &students[i].id, &students[i].score);
    }

    qsort(students, n, sizeof(Student), compare);

    int threshold = students[m - 1].score;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (students[i].score >= threshold) {
            count++;
        }
    }

    printf("%d %d\n", threshold, count);

    for (int i = 0; i < n; i++) {
        if (students[i].score >= threshold) {
            printf("%d %d\n", students[i].id, students[i].score);
        }
    }

    return 0;
}