#include <stdio.h>
#include <string.h>

int main() {
    int k;
    scanf("%d", &k);
    char s[256];
    scanf("%s", s);
    int len = strlen(s);

    // Define the digits and their corresponding patterns
    char digits[10][5][4] = {
        {"--", "  |", "  |", "    "}, // 0
        {"  ", "  |", "  |", "    "}, // 1
        {"--", "  |", "--", "    "}, // 2
        {"--", "  |", "  --", "    "}, // 3
        {"  ", "  |", "  --", "    "}, // 4
        {"--", " --", "  --", "    "}, // 5
        {"--", " --", "--  ", "    "}, // 6
        {"--", "  |", "  | ", "    "}, // 7
        {"--", "-- ", "-- ", "    "}, // 8
        {"--", "-- ", "  --", "    "}  // 9
    };

    // Print the top line of each digit
    for (int i = 0; i < len; i++) {
        int digit = s[i] - '0';
        printf("%s", digits[digit][0]);
        if (i != len - 1) {
            printf("   ");
        }
    }
    printf("\n");

    // Print the middle line of each digit
    for (int i = 0; i < len; i++) {
        int digit = s[i] - '0';
        printf("%s", digits[digit][1]);
        if (i != len - 1) {
            printf("   ");
        }
    }
    printf("\n");

    // Print the bottom line of each digit
    for (int i = 0; i < len; i++) {
        int digit = s[i] - '0';
        printf("%s", digits[digit][2]);
        if (i != len - 1) {
            printf("   ");
        }
    }
    printf("\n");

    // Print the last line of each digit
    for (int i = 0; i < len; i++) {
        int digit = s[i] - '0';
        printf("%s", digits[digit][3]);
        if (i != len - 1) {
            printf("   ");
        }
    }
    printf("\n");

    return 0;
}