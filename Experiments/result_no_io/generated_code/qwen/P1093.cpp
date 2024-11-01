#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 300

typedef struct {
    int id;
    int scores[3];
    int total_score;
} Student;

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    
    if (studentA->total_score != studentB->total_score) {
        return studentB->total_score - studentA->total_score;
    } else if (studentA->scores[0] != studentB->scores[0]) {
        return studentB->scores[0] - studentA->scores[0];
    } else {
        return studentA->id - studentB->id;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    Student students[MAX_STUDENTS];
    
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        scanf("%d %d %d", &students[i].scores[0], &students[i].scores[1], &students[i].scores[2]);
        students[i].total_score = students[i].scores[0] + students[i].scores[1] + students[i].scores[2];
    }
    
    qsort(students, n, sizeof(Student), compare);
    
    for (int i = 0; i < 5 && i < n; i++) {
        printf("%d %d\n", students[i].id, students[i].total_score);
    }
    
    return 0;
}