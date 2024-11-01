#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    int year;
    int month;
    int day;
} Student;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int compare(Student a, Student b) {
    if (a.year != b.year) return a.year - b.year;
    if (a.month != b.month) return a.month - b.month;
    if (a.day != b.day) return a.day - b.day;
    return 0; // 生日相同，不交换
}

void sortStudents(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(students[j], students[j + 1]) > 0) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Student students[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", students[i].name, &students[i].year, &students[i].month, &students[i].day);
    }

    sortStudents(students, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", students[i].name);
    }

    return 0;
}