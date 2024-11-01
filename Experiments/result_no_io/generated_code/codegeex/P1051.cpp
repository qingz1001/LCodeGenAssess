#include <stdio.h>
#include <string.h>

struct Student {
    char name[21];
    int final_grade;
    int class_grade;
    char is_student_council;
    char is_western;
    int papers;
    int total_scholarship;
};

int main() {
    int N;
    scanf("%d", &N);

    struct Student students[101];
    int max_scholarship = 0;
    int max_index = 0;
    int total_scholarship = 0;

    for (int i = 0; i < N; i++) {
        scanf("%s %d %d %c %c %d", students[i].name, &students[i].final_grade, &students[i].class_grade, &students[i].is_student_council, &students[i].is_western, &students[i].papers);
        students[i].total_scholarship = 0;

        if (students[i].final_grade > 80 && students[i].papers >= 1) {
            students[i].total_scholarship += 8000;
        }
        if (students[i].final_grade > 85 && students[i].class_grade > 80) {
            students[i].total_scholarship += 4000;
        }
        if (students[i].final_grade > 90) {
            students[i].total_scholarship += 2000;
        }
        if (students[i].final_grade > 85 && students[i].is_western == 'Y') {
            students[i].total_scholarship += 1000;
        }
        if (students[i].class_grade > 80 && students[i].is_student_council == 'Y') {
            students[i].total_scholarship += 850;
        }

        total_scholarship += students[i].total_scholarship;

        if (students[i].total_scholarship > max_scholarship) {
            max_scholarship = students[i].total_scholarship;
            max_index = i;
        }
    }

    printf("%s\n%d\n%d\n", students[max_index].name, students[max_index].total_scholarship, total_scholarship);

    return 0;
}