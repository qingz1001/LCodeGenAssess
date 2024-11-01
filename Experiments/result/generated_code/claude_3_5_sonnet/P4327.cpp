#include <stdio.h>
#include <string.h>

void printFrame(char *word) {
    int len = strlen(word);
    char frame[5][5*len+1];
    memset(frame, '.', sizeof(frame));

    for (int i = 0; i < len; i++) {
        int col = 4*i;
        if ((i+1) % 3 == 0) {
            frame[0][col+2] = '*';
            frame[1][col+1] = frame[1][col+3] = '*';
            frame[2][col] = frame[2][col+4] = '*';
            frame[3][col+1] = frame[3][col+3] = '*';
            frame[4][col+2] = '*';
        } else {
            frame[0][col+2] = '#';
            frame[1][col+1] = frame[1][col+3] = '#';
            frame[2][col] = frame[2][col+4] = '#';
            frame[3][col+1] = frame[3][col+3] = '#';
            frame[4][col+2] = '#';
        }
        frame[2][col+2] = word[i];
    }

    for (int i = 0; i < 5; i++) {
        frame[i][5*len-1] = '\0';
        printf("%s\n", frame[i]);
    }
}

int main() {
    char word[16];
    scanf("%s", word);
    printFrame(word);
    return 0;
}