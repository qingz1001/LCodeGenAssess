#include <stdio.h>
#include <string.h>

void printDigit(int digit, int k) {
    char nums[10][5][3] = {
        {{" - ","| |","   ","| |"," - "}},
        {{"   ","  |","   ","  |","   "}},
        {{" - ","  |"," - ","|  "," - "}},
        {{" - ","  |"," - ","  |"," - "}},
        {{"   ","| |"," - ","  |","   "}},
        {{" - ","|  "," - ","  |"," - "}},
        {{" - ","|  "," - ","| |"," - "}},
        {{" - ","  |","   ","  |","   "}},
        {{" - ","| |"," - ","| |"," - "}},
        {{" - ","| |"," - ","  |"," - "}}
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < k; j++) {
            if (i % 2 == 0) {
                for (int l = 0; l < k; l++) {
                    printf("%c", nums[digit][i][1]);
                }
                printf("%c", nums[digit][i][2]);
            } else {
                printf("%c", nums[digit][i][0]);
                for (int l = 0; l < k; l++) {
                    printf(" ");
                }
                printf("%c", nums[digit][i][2]);
            }
        }
        printf("\n");
    }
}

int main() {
    int k;
    char s[256];
    scanf("%d", &k);
    scanf("%s", s);

    int len = strlen(s);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < len; j++) {
            if (j > 0) printf(" ");
            int digit = s[j] - '0';
            for (int l = 0; l < k; l++) {
                if (i % 2 == 0) {
                    for (int m = 0; m < k; m++) {
                        printf("%c", "0-| "[digit][i][1]);
                    }
                    printf("%c", "0-| "[digit][i][2]);
                } else {
                    printf("%c", "0-| "[digit][i][0]);
                    for (int m = 0; m < k; m++) {
                        printf(" ");
                    }
                    printf("%c", "0-| "[digit][i][2]);
                }
            }
        }
        printf("\n");
    }

    return 0;
}