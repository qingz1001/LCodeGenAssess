#include <stdio.h>
#include <string.h>

void printDigit(int digit, int k, int row) {
    char patterns[10][5][4] = {
        {" - ","| |","   ","| |"," - "},
        {"   ","  |","   ","  |","   "},
        {" - ","  |"," - ","|  "," - "},
        {" - ","  |"," - ","  |"," - "},
        {"   ","| |"," - ","  |","   "},
        {" - ","|  "," - ","  |"," - "},
        {" - ","|  "," - ","| |"," - "},
        {" - ","  |","   ","  |","   "},
        {" - ","| |"," - ","| |"," - "},
        {" - ","| |"," - ","  |"," - "}
    };

    for (int i = 0; i < 3; i++) {
        if (row == 0 && i == 1) printf("%s", patterns[digit][0]);
        else if (row == k+1 && i == 1) printf("%s", patterns[digit][2]);
        else if (row == 2*k+2 && i == 1) printf("%s", patterns[digit][4]);
        else if (row > 0 && row <= k) printf("%s", patterns[digit][1]);
        else if (row > k+1 && row <= 2*k+1) printf("%s", patterns[digit][3]);
        else printf("   ");
    }
}

int main() {
    int k;
    char s[256];
    scanf("%d", &k);
    scanf("%s", s);

    int len = strlen(s);
    for (int row = 0; row < 2*k+3; row++) {
        for (int i = 0; i < len; i++) {
            if (i > 0) printf(" ");
            printDigit(s[i] - '0', k, row);
        }
        printf("\n");
    }

    return 0;
}