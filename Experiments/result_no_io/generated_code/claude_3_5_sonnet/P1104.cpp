#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 20
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int year;
    int month;
    int day;
} Student;

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;

    if (studentA->year != studentB->year)
        return studentB->year - studentA->year;
    if (studentA->month != studentB->month)
        return studentB->month - studentA->month;
    if (studentA->day != studentB->day)
        return studentB->day - studentA->day;
    return 1;  // 如果生日相同，保持输入顺序
}

int main() {
    int n;
    scanf("%d", &n);

    Student students[MAX_STUDENTS];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", students[i].name, &students[i].year, &students[i].month, &students[i].day);
    }

    qsort(students, n, sizeof(Student), compare);

    for (int i = 0; i < n; i++) {
        printf("%s\n", students[i].name);
    }

    return 0;
}