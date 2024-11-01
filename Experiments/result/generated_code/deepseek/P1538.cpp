#include <stdio.h>
#include <string.h>

void print_digit(int k, char digit) {
    char segments[10][5][4] = {
        {" -- ", "|  |", "|  |", " -- ", "    "}, // 0
        {"    ", "   |", "   |", "    ", "    "}, // 1
        {" -- ", "   |", " -- ", "|   ", " -- "}, // 2
        {" -- ", "   |", " -- ", "   |", " -- "}, // 3
        {"    ", "|  |", " -- ", "   |", "    "}, // 4
        {" -- ", "|   ", " -- ", "   |", " -- "}, // 5
        {" -- ", "|   ", " -- ", "|  |", " -- "}, // 6
        {" -- ", "   |", "   |", "   |", "    "}, // 7
        {" -- ", "|  |", " -- ", "|  |", " -- "}, // 8
        {" -- ", "|  |", " -- ", "   |", " -- "}  // 9
    };

    for (int i = 0; i < 5; i++) {
        if (i == 1 || i == 2 || i == 3) {
            for (int j = 0; j < k; j++) {
                printf("%s", segments[digit - '0'][i]);
                for (int l = 0; l < k; l++) {
                    if (i == 1 || i == 3) {
                        printf(" ");
                    } else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        } else {
            printf("%s", segments[digit - '0'][i]);
            for (int j = 0; j < k; j++) {
                printf(" ");
            }
            printf("\n");
        }
    }
}

int main() {
    int k;
    char s[256];
    scanf("%d", &k);
    scanf("%s", s);

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        print_digit(k, s[i]);
        if (i < len - 1) {
            printf("\n");
        }
    }

    return 0;
}