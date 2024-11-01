#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CARDS 16

int calcScore(char cards[MAX_CARDS][3], int cardCount) {
    int score = 0;
    bool hasS12 = false, hasD11 = false, hasC10 = false;
    int heartCount = 0;
    
    for (int i = 0; i < cardCount; i++) {
        if (strcmp(cards[i], "S12") == 0) hasS12 = true;
        else if (strcmp(cards[i], "D11") == 0) hasD11 = true;
        else if (strcmp(cards[i], "C10") == 0) hasC10 = true;
        else if (cards[i][0] == 'H') heartCount++;
    }
    
    if (cardCount == 0) return 0;
    if (cardCount == 16) return 1000;
    
    if (heartCount == 13) {
        score += 200;
        if (hasS12 && hasD11) score += 300;
    } else {
        int heartScores[] = {-50,-2,-3,-4,-5,-6,-7,-8,-9,-10,-20,-30,-40};
        for (int i = 0; i < cardCount; i++) {
            if (cards[i][0] == 'H') {
                score += heartScores[cards[i][1] - '0' - (cards[i][1] == '1' ? 0 : 1)];
            }
        }
        if (hasS12) score -= 100;
        if (hasD11) score += 100;
    }
    
    if (hasC10) {
        if (cardCount == 1) score = 50;
        else score *= 2;
    }
    
    return score;
}

int main() {
    int cardCounts[4];
    char cards[4][MAX_CARDS][3];
    
    while (1) {
        bool allZero = true;
        for (int i = 0; i < 4; i++) {
            scanf("%d", &cardCounts[i]);
            if (cardCounts[i] != 0) allZero = false;
            for (int j = 0; j < cardCounts[i]; j++) {
                scanf("%s", cards[i][j]);
            }
        }
        
        if (allZero) break;
        
        for (int i = 0; i < 4; i++) {
            int score = calcScore(cards[i], cardCounts[i]);
            if (i > 0) printf(" ");
            if (score > 0) printf("+");
            printf("%d", score);
        }
        printf("\n");
    }
    
    return 0;
}