#include <stdio.h>
#include <string.h>

int main() {
    char s[51];
    int fingers[4] = {0, 0, 0, 0}; // 指尖的编号：0-小指，1-无名指，2-中指，3-食指

    scanf("%s", s);

    for (int i = 0; i < strlen(s); i++) {
        switch (s[i]) {
            case '5': case 'T': case 'G': case 'B':
                fingers[0]++;
                break;
            case '6': case 'Y': case 'H': case 'N':
                fingers[1]++;
                break;
            case '7': case 'U': case 'F': case 'K':
                fingers[2]++;
                break;
            case '8': case 'I': case 'J': case 'L':
                fingers[3]++;
                break;
            default:
                break;
        }
    }

    printf("%d\n%d\n%d\n", fingers[0], fingers[1], fingers[2], fingers[3]);

    return 0;
}