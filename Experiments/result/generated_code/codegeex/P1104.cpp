#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    int year;
    int month;
    int day;
} Student;

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    
    // Compare by year
    if (studentA->year != studentB->year) {
        return studentA->year - studentB->year;
    }
    
    // Compare by month
    if (studentA->month != studentB->month) {
        return studentA->month - studentB->month;
    }
    
    // Compare by day
    return studentA->day - studentB->day;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Student students[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", students[i].name, &students[i].year, &students[i].month, &students[i].day);
    }
    
    qsort(students, n, sizeof(Student), compare);
    
    for (int i = 0; i < n; i++) {
        printf("%s\n", students[i].name);
    }
    
    return 0;
}