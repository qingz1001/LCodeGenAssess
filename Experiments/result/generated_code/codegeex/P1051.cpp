#include <stdio.h>
#include <string.h>

struct Student {
    char name[21];
    int score;
    int class_score;
    char student_officer;
    char west;
    int paper_count;
    int scholarship;
};

int main() {
    int N;
    scanf("%d", &N);
    
    struct Student students[100];
    int total_scholarship = 0;
    int max_scholarship = 0;
    int max_index = 0;

    for (int i = 0; i < N; i++) {
        scanf("%s %d %d %c %c %d", students[i].name, &students[i].score, &students[i].class_score, &students[i].student_officer, &students[i].west, &students[i].paper_count);
        students[i].scholarship = 0;

        if (students[i].score > 80 && students[i].paper_count >= 1) {
            students[i].scholarship += 8000;
        }
        if (students[i].score > 85 && students[i].class_score > 80) {
            students[i].scholarship += 4000;
        }
        if (students[i].score > 90) {
            students[i].scholarship += 2000;
        }
        if (students[i].score > 85 && students[i].west == 'Y') {
            students[i].scholarship += 1000;
        }
        if (students[i].class_score > 80 && students[i].student_officer == 'Y') {
            students[i].scholarship += 850;
        }

        total_scholarship += students[i].scholarship;

        if (students[i].scholarship > max_scholarship) {
            max_scholarship = students[i].scholarship;
            max_index = i;
        }
    }

    printf("%s\n%d\n%d\n", students[max_index].name, max_scholarship, total_scholarship);

    return 0;
}