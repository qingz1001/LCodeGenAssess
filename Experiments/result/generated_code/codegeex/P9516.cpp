#include <stdio.h>

int main() {
    int base, community, contest, practice, achievement;
    scanf("%d%d%d%d%d", &base, &community, &contest, &practice, &achievement);
    
    int score = base + community + contest + practice + achievement;
    
    if (score >= 0 && score <= 140) {
        printf("Gray\n");
    } else if (score > 140 && score <= 350) {
        printf("Blue\n");
    } else if (score > 350 && score <= 640) {
        printf("Green\n");
    } else if (score > 640 && score <= 930) {
        printf("Orange\n");
    } else if (score > 930) {
        printf("Red\n");
    }
    
    return 0;
}