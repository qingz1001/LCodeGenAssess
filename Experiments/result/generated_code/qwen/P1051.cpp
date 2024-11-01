#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 21

typedef struct {
    char name[MAX_NAME_LENGTH];
    int average_score;
    int class_evaluation;
    int is_class_officer;
    int is_western_student;
    int publications;
} Student;

int main() {
    int N;
    scanf("%d", &N);

    Student students[N];
    for (int i = 0; i < N; i++) {
        scanf("%s %d %d %c %c %d",
              students[i].name,
              &students[i].average_score,
              &students[i].class_evaluation,
              &students[i].is_class_officer,
              &students[i].is_western_student,
              &students[i].publications);
    }

    int max_bonus = 0;
    int total_bonus = 0;
    int index_of_max_bonus = -1;

    for (int i = 0; i < N; i++) {
        int bonus = 0;

        if (students[i].average_score > 80 && students[i].publications >= 1) {
            bonus += 8000;
        }
        if (students[i].average_score > 85 && students[i].class_evaluation > 80) {
            bonus += 4000;
        }
        if (students[i].average_score > 90) {
            bonus += 2000;
        }
        if (students[i].average_score > 85 && students[i].is_western_student == 'Y') {
            bonus += 1000;
        }
        if (students[i].class_evaluation > 80 && students[i].is_class_officer == 'Y') {
            bonus += 850;
        }

        total_bonus += bonus;

        if (bonus > max_bonus) {
            max_bonus = bonus;
            index_of_max_bonus = i;
        }
    }

    printf("%s\n", students[index_of_max_bonus].name);
    printf("%d\n", max_bonus);
    printf("%d\n", total_bonus);

    return 0;
}