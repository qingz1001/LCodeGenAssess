#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 21

typedef struct {
    char name[MAX_NAME_LENGTH];
    int final_score;
    int class_score;
    char is_leader;
    char is_western;
    int papers;
    int total_scholarship;
} Student;

int calculate_scholarship(Student *student) {
    int scholarship = 0;
    if (student->final_score > 80 && student->papers >= 1) {
        scholarship += 8000;
    }
    if (student->final_score > 85 && student->class_score > 80) {
        scholarship += 4000;
    }
    if (student->final_score > 90) {
        scholarship += 2000;
    }
    if (student->final_score > 85 && student->is_western == 'Y') {
        scholarship += 1000;
    }
    if (student->class_score > 80 && student->is_leader == 'Y') {
        scholarship += 850;
    }
    return scholarship;
}

int main() {
    int N;
    scanf("%d", &N);

    Student students[MAX_STUDENTS];
    int max_scholarship = 0;
    int total_scholarship = 0;
    char max_scholarship_name[MAX_NAME_LENGTH];

    for (int i = 0; i < N; i++) {
        scanf("%s %d %d %c %c %d", 
              students[i].name, 
              &students[i].final_score, 
              &students[i].class_score, 
              &students[i].is_leader, 
              &students[i].is_western, 
              &students[i].papers);

        students[i].total_scholarship = calculate_scholarship(&students[i]);
        total_scholarship += students[i].total_scholarship;

        if (students[i].total_scholarship > max_scholarship) {
            max_scholarship = students[i].total_scholarship;
            strcpy(max_scholarship_name, students[i].name);
        }
    }

    printf("%s\n", max_scholarship_name);
    printf("%d\n", max_scholarship);
    printf("%d\n", total_scholarship);

    return 0;
}