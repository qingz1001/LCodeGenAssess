#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 21

struct Student {
    char name[MAX_NAME_LENGTH];
    int avgScore;
    int classScore;
    char isLeader;
    char isWestern;
    int papers;
    int scholarship;
};

int calculateScholarship(struct Student *s) {
    int total = 0;
    if (s->avgScore > 80 && s->papers >= 1) total += 8000;
    if (s->avgScore > 85 && s->classScore > 80) total += 4000;
    if (s->avgScore > 90) total += 2000;
    if (s->avgScore > 85 && s->isWestern == 'Y') total += 1000;
    if (s->classScore > 80 && s->isLeader == 'Y') total += 850;
    return total;
}

int main() {
    int n;
    scanf("%d", &n);

    struct Student students[MAX_STUDENTS];
    int maxScholarship = 0;
    int maxIndex = 0;
    int totalScholarship = 0;

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %c %c %d", 
            students[i].name, 
            &students[i].avgScore, 
            &students[i].classScore, 
            &students[i].isLeader, 
            &students[i].isWestern, 
            &students[i].papers);

        students[i].scholarship = calculateScholarship(&students[i]);
        totalScholarship += students[i].scholarship;

        if (students[i].scholarship > maxScholarship) {
            maxScholarship = students[i].scholarship;
            maxIndex = i;
        }
    }

    printf("%s\n", students[maxIndex].name);
    printf("%d\n", maxScholarship);
    printf("%d\n", totalScholarship);

    return 0;
}