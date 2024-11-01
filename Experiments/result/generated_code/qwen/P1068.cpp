#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int score;
} Student;

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    if (studentA->score != studentB->score) {
        return studentB->score - studentA->score;
    }
    return studentA->id - studentB->id;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Student students[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &students[i].id, &students[i].score);
    }

    qsort(students, n, sizeof(Student), compare);

    int cutoff = students[m * 150 / 100 - 1].score;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].score >= cutoff) {
            printf("%d %d\n", students[i].id, students[i].score);
            count++;
        }
    }

    printf("%d %d\n", cutoff, count);

    return 0;
}