#include <stdio.h>

int main() {
    int credit, contribution, competition, practice, achievement;
    scanf("%d %d %d %d %d", &credit, &contribution, &competition, &practice, &achievement);

    int total = credit + contribution + competition + practice + achievement;

    if (total >= 0 && total < 50) {
        printf("Gray\n");
    } else if (total >= 50 && total < 150) {
        printf("Blue\n");
    } else if (total >= 150 && total < 250) {
        printf("Green\n");
    } else if (total >= 250 && total < 400) {
        printf("Orange\n");
    } else if (total >= 400) {
        printf("Red\n");
    }

    return 0;
}