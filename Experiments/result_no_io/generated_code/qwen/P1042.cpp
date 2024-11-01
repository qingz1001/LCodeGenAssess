#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 26
#define MAX_LINES 2501

void process_game(char *game, int score[], int target) {
    int p1 = 0, p2 = 0;
    for (int i = 0; game[i] != '\0'; i++) {
        if (game[i] == 'W') {
            p1++;
        } else if (game[i] == 'L') {
            p2++;
        }
        if (p1 >= target || p2 >= target) {
            break;
        }
    }
    printf("%d %d\n", p1, p2);
}

int main() {
    char games[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;

    while (fgets(games[line_count], MAX_LINE_LENGTH, stdin)) {
        if (games[line_count][0] == 'E') {
            break;
        }
        line_count++;
    }

    for (int i = 0; i < line_count; i++) {
        printf("11 分制:\n");
        process_game(games[i], NULL, 11);
        printf("\n21 分制:\n");
        process_game(games[i], NULL, 21);
        printf("\n");
    }

    return 0;
}