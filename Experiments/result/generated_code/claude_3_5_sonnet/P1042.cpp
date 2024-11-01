#include <stdio.h>
#include <string.h>

#define MAX_LEN 30
#define MAX_LINES 2501

void print_score(int w, int l) {
    printf("%d:%d\n", w, l);
}

void process_game(char games[MAX_LINES][MAX_LEN], int lines) {
    int w11 = 0, l11 = 0, w21 = 0, l21 = 0;
    int game11 = 1, game21 = 1;

    // 11分制
    for (int i = 0; i < lines; i++) {
        for (int j = 0; games[i][j] != '\0' && games[i][j] != 'E'; j++) {
            if (games[i][j] == 'W') w11++;
            else if (games[i][j] == 'L') l11++;

            if ((w11 >= 11 || l11 >= 11) && abs(w11 - l11) >= 2) {
                print_score(w11, l11);
                w11 = 0;
                l11 = 0;
                game11++;
            }
        }
    }
    if (w11 > 0 || l11 > 0) {
        print_score(w11, l11);
    }

    printf("\n");

    // 21分制
    for (int i = 0; i < lines; i++) {
        for (int j = 0; games[i][j] != '\0' && games[i][j] != 'E'; j++) {
            if (games[i][j] == 'W') w21++;
            else if (games[i][j] == 'L') l21++;

            if ((w21 >= 21 || l21 >= 21) && abs(w21 - l21) >= 2) {
                print_score(w21, l21);
                w21 = 0;
                l21 = 0;
                game21++;
            }
        }
    }
    if (w21 > 0 || l21 > 0) {
        print_score(w21, l21);
    }
}

int main() {
    char games[MAX_LINES][MAX_LEN];
    int lines = 0;

    while (fgets(games[lines], MAX_LEN, stdin) != NULL && lines < MAX_LINES) {
        if (strchr(games[lines], 'E') != NULL) {
            break;
        }
        lines++;
    }

    process_game(games, lines);

    return 0;
}