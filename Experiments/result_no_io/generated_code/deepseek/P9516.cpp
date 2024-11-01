#include <stdio.h>

int main() {
    int credit, contribution, competition, practice, achievement;
    scanf("%d %d %d %d %d", &credit, &contribution, &competition, &practice, &achievement);

    int total_score = credit + contribution + competition + practice + achievement;

    if (total_score >= 400) {
        printf("Red\n");
    } else if (total_score >= 300) {
        printf("Orange\n");
    } else if (total_score >= 200) {
        printf("Green\n");
    } else if (total_score >= 100) {
        printf("Blue\n");
    } else {
        printf("Gray\n");
    }

    return 0;
}