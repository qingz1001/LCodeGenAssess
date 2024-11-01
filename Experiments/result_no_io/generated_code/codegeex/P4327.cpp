#include <stdio.h>
#include <string.h>

int main() {
    char s[20];
    scanf("%s", s);
    int n = strlen(s);

    // Define the frames
    char PeterPan[5][5] = {
        "..#..",
        ".#.#.",
        "#.X.#",
        ".#.#.",
        "..#.."
    };

    char WendyFrame[5][5] = {
        "..*..",
        ".*.*.",
        "*.X.*",
        ".*.*.",
        "..*.."
    };

    // Print the frames
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < n; j++) {
            if ((j + 1) % 3 == 0) {
                // Print Wendy frame
                for (int k = 0; k < 5; k++) {
                    printf("%c", WendyFrame[i][k]);
                }
            } else {
                // Print Peter Pan frame
                for (int k = 0; k < 5; k++) {
                    printf("%c", PeterPan[i][k]);
                }
            }
            // Print the letter
            printf("%c", s[j]);
        }
        printf("\n");
    }

    return 0;
}