#include <stdio.h>

int main() {
    int credit, contribution, competition, practice, achievement;
    scanf("%d %d %d %d %d", &credit, &contribution, &competition, &practice, &achievement);

    int total = credit + contribution + competition + practice + achievement;

    if (total >= 270) {
        printf("Red\n");
    } else if (total >= 210) {
        printf("Orange\n");
    } else if (total >= 150) {
        printf("Green\n");
    } else if (total >= 90) {
        printf("Blue\n");
    } else {
        printf("Gray\n");
    }

    return 0;
}