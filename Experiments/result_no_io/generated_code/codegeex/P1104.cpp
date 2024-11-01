#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    int year;
    int month;
    int day;
    int index;
} Student;

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;

    // 比较年份
    if (studentA->year != studentB->year) {
        return studentA->year - studentB->year;
    }

    // 比较月份
    if (studentA->month != studentB->month) {
        return studentA->month - studentB->month;
    }

    // 比较日期
    if (studentA->day != studentB->day) {
        return studentA->day - studentB->day;
    }

    // 比较输入顺序
    return studentA->index - studentB->index;
}

int main() {
    int n;
    scanf("%d", &n);

    Student students[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", students[i].name, &students[i].year, &students[i].month, &students[i].day);
        students[i].index = i;
    }

    qsort(students, n, sizeof(Student), compare);

    for (int i = 0; i < n; i++) {
        printf("%s\n", students[i].name);
    }

    return 0;
}