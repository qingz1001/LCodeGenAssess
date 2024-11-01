#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int chinese;
    int math;
    int english;
    int total;
} Student;

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;

    if (studentA->total != studentB->total) {
        return studentB->total - studentA->total;
    } else if (studentA->chinese != studentB->chinese) {
        return studentB->chinese - studentA->chinese;
    } else {
        return studentA->id - studentB->id;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Student students[n];

    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        scanf("%d %d %d", &students[i].chinese, &students[i].math, &students[i].english);
        students[i].total = students[i].chinese + students[i].math + students[i].english;
    }

    qsort(students, n, sizeof(Student), compare);

    for (int i = 0; i < 5; i++) {
        printf("%d %d\n", students[i].id, students[i].total);
    }

    return 0;
}