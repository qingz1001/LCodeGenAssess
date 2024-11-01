#include <stdio.h>
#include <string.h>

typedef struct {
    char name[21];
    int final_score;
    int class_score;
    char is_leader;
    char is_western;
    int paper_count;
    int total_scholarship;
} Student;

int main() {
    int N;
    scanf("%d", &N);
    Student students[N];
    int max_scholarship = 0;
    int total_scholarship = 0;
    char max_scholarship_name[21];

    for (int i = 0; i < N; i++) {
        scanf("%s %d %d %c %c %d", students[i].name, &students[i].final_score, &students[i].class_score, &students[i].is_leader, &students[i].is_western, &students[i].paper_count);
        students[i].total_scholarship = 0;

        if (students[i].final_score > 80 && students[i].paper_count >= 1) {
            students[i].total_scholarship += 8000;
        }
        if (students[i].final_score > 85 && students[i].class_score > 80) {
            students[i].total_scholarship += 4000;
        }
        if (students[i].final_score > 90) {
            students[i].total_scholarship += 2000;
        }
        if (students[i].final_score > 85 && students[i].is_western == 'Y') {
            students[i].total_scholarship += 1000;
        }
        if (students[i].class_score > 80 && students[i].is_leader == 'Y') {
            students[i].total_scholarship += 850;
        }

        total_scholarship += students[i].total_scholarship;

        if (students[i].total_scholarship > max_scholarship) {
            max_scholarship = students[i].total_scholarship;
            strcpy(max_scholarship_name, students[i].name);
        }
    }

    printf("%s\n%d\n%d\n", max_scholarship_name, max_scholarship, total_scholarship);

    return 0;
}