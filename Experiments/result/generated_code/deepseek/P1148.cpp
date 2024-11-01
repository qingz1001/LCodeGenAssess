#include <stdio.h>
#include <string.h>

#define MAX_CARDS 16

int calculate_score(int count, char cards[][5]) {
    int score = 0;
    int has_C10 = 0;
    int has_S12 = 0;
    int has_D11 = 0;
    int has_all_hearts = 1;
    int hearts_count = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(cards[i], "C10") == 0) {
            has_C10 = 1;
        } else if (strcmp(cards[i], "S12") == 0) {
            has_S12 = 1;
            score -= 100;
        } else if (strcmp(cards[i], "D11") == 0) {
            has_D11 = 1;
            score += 100;
        } else if (cards[i][0] == 'H') {
            hearts_count++;
            int value = 0;
            switch (cards[i][1]) {
                case '1':
                    if (cards[i][2] == '0') {
                        value = -40;
                    } else {
                        value = -50;
                    }
                    break;
                case '2': value = -2; break;
                case '3': value = -3; break;
                case '4': value = -4; break;
                case '5': value = -5; break;
                case '6': value = -6; break;
                case '7': value = -7; break;
                case '8': value = -8; break;
                case '9': value = -9; break;
                case '1': value = -10; break;
                case '2': value = -20; break;
                case '3': value = -30; break;
                default: break;
            }
            score += value;
        }
    }

    if (hearts_count == 13) {
        score = 200;
        if (has_S12 && has_D11) {
            score = 500;
        }
    }

    if (has_C10) {
        if (count == 1) {
            score += 50;
        } else {
            score *= 2;
        }
    }

    return score;
}

int main() {
    int count;
    char cards[4][MAX_CARDS][5];
    int scores[4];

    while (1) {
        int total_count = 0;
        for (int i = 0; i < 4; i++) {
            scanf("%d", &count);
            total_count += count;
            for (int j = 0; j < count; j++) {
                scanf("%s", cards[i][j]);
            }
        }

        if (total_count == 0) break;

        for (int i = 0; i < 4; i++) {
            scores[i] = calculate_score(count, cards[i]);
        }

        for (int i = 0; i < 4; i++) {
            if (i > 0) printf(" ");
            printf("%+d", scores[i]);
        }
        printf("\n");
    }

    return 0;
}