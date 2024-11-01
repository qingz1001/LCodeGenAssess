#include <stdio.h>

int main() {
    int baseCredit, communityContribution, competition, practice, achievements;
    scanf("%d %d %d %d %d", &baseCredit, &communityContribution, &competition, &practice, &achievements);
    
    int totalScore = baseCredit + communityContribution + competition + practice + achievements;
    
    if (totalScore >= 240) {
        printf("Red\n");
    } else if (totalScore >= 120) {
        printf("Orange\n");
    } else if (totalScore >= 60) {
        printf("Green\n");
    } else if (totalScore >= 20) {
        printf("Blue\n");
    } else {
        printf("Gray\n");
    }
    
    return 0;
}