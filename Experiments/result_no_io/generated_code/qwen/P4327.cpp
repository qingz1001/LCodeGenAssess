#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 16

void printFrame(char ch, int type) {
    if (type == 0) { // Peter Pan frame
        printf("..#..\n");
        printf(".%c.#\n", ch);
        printf("#.%c#\n", ch);
        printf(".%c.#\n", ch);
        printf("..#..\n");
    } else { // Wendy frame
        printf("..*..\n");
        printf(".%c.*\n", ch);
        printf("*.%c*\n", ch);
        printf(".%c.*\n", ch);
        printf("..*..\n");
    }
}

int main() {
    char word[MAX_LENGTH];
    scanf("%s", word);
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        if ((i + 1) % 3 == 0) {
            printFrame(word[i], 1); // Wendy frame
        } else {
            printFrame(word[i], 0); // Peter Pan frame
        }
    }

    return 0;
}