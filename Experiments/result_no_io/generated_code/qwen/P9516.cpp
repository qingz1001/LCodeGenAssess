#include <stdio.h>

int main() {
    int credit, contribution, competition, practice, achievement;
    scanf("%d %d %d %d %d", &credit, &contribution, &competition, &practice, &achievement);

    if (credit >= 90 && contribution >= 90 && competition >= 90 && practice >= 90 && achievement >= 90) {
        printf("Red\n");
    } else if (credit >= 75 && contribution >= 75 && competition >= 75 && practice >= 75 && achievement >= 75) {
        printf("Orange\n");
    } else if (credit >= 60 && contribution >= 60 && competition >= 60 && practice >= 60 && achievement >= 60) {
        printf("Green\n");
    } else if (credit >= 45 && contribution >= 45 && competition >= 45 && practice >= 45 && achievement >= 45) {
        printf("Blue\n");
    } else {
        printf("Gray\n");
    }

    return 0;
}