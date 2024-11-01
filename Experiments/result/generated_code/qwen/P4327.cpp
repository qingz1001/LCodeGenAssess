#include <stdio.h>
#include <string.h>

#define MAX_LEN 15

void printFrame(char ch, int isWendy) {
    if (isWendy) {
        printf("..*..\n");
        printf(".*.%c*\n", ch);
        printf("*.%c.*\n", ch);
        printf(".*.%c*\n", ch);
        printf("..*..\n");
    } else {
        printf("..#..\n");
        printf(".%c.#.\n", ch);
        printf("#%c.##\n", ch);
        printf(".%c.#.\n", ch);
        printf("..#..\n");
    }
}

int main() {
    char word[MAX_LEN + 1];
    scanf("%s", word);

    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if ((i + 1) % 3 == 0) {
            printFrame(word[i], 1); // Wendy frame
        } else {
            printFrame(word[i], 0); // Peter Pan frame
        }
    }

    return 0;
}