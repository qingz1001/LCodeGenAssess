#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 21

struct Student {
    char name[MAX_NAME_LENGTH];
    int average_score;
    int class_score;
    char is_leader;
    char is_western;
    int papers;
    int scholarship;
};

int calculate_scholarship(struct Student *s) {
    int total = 0;
    if (s->average_score > 80 && s->papers >= 1) total += 8000;
    if (s->average_score > 85 && s->class_score > 80) total += 4000;
    if (s->average_score > 90) total += 2000;
    if (s->average_score > 85 && s->is_western == 'Y') total += 1000;
    if (s->class_score > 80 && s->is_leader == 'Y') total += 850;
    return total;
}

int main() {
    int n;
    scanf("%d", &n);

    struct Student students[MAX_STUDENTS];
    int total_scholarship = 0;
    int max_scholarship = 0;
    char top_student[MAX_NAME_LENGTH];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %c %c %d", 
              students[i].name, 
              &students[i].average_score, 
              &students[i].class_score, 
              &students[i].is_leader, 
              &students[i].is_western, 
              &students[i].papers);

        students[i].scholarship = calculate_scholarship(&students[i]);
        total_scholarship += students[i].scholarship;

        if (students[i].scholarship > max_scholarship) {
            max_scholarship = students[i].scholarship;
            strcpy(top_student, students[i].name);
        }
    }

    printf("%s\n", top_student);
    printf("%d\n", max_scholarship);
    printf("%d\n", total_scholarship);

    return 0;
}