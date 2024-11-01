#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 21
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int average_score;
    int class_evaluation;
    int is_class_officer;
    int is_western_student;
    int papers_published;
} Student;

int main() {
    int N, max_bonus = 0, total_bonus = 0;
    Student students[MAX_STUDENTS];
    Student max_beneficiary;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%s %d %d %d %d %d",
              students[i].name,
              &students[i].average_score,
              &students[i].class_evaluation,
              &students[i].is_class_officer,
              &students[i].is_western_student,
              &students[i].papers_published);

        int bonus = 0;

        if (students[i].average_score > 80 && students[i].papers_published >= 1) {
            bonus += 8000;
        }
        if (students[i].average_score > 85 && students[i].class_evaluation > 80) {
            bonus += 4000;
        }
        if (students[i].average_score > 90) {
            bonus += 2000;
        }
        if (students[i].average_score > 85 && students[i].is_western_student == 1) {
            bonus += 1000;
        }
        if (students[i].class_evaluation > 80 && students[i].is_class_officer == 1) {
            bonus += 850;
        }

        total_bonus += bonus;

        if (bonus > max_bonus) {
            max_bonus = bonus;
            strcpy(max_beneficiary.name, students[i].name);
        }
    }

    printf("%s\n%d\n%d\n", max_beneficiary.name, max_bonus, total_bonus);

    return 0;
}