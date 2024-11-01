#include <stdio.h>
#include <string.h>

int main() {
    char s[51];
    int fingers[8] = {0}; // 8 fingers excluding the thumb
    char *finger_keys[8] = {
        "1QAZ", "2WSX", "3EDC", "4RFV5TGB",
        "6YHN7UJM", "8IK,", "9OL.", "0P;/-['=]"
    };

    scanf("%s", s);

    for (int i = 0; i < strlen(s); i++) {
        for (int j = 0; j < 8; j++) {
            if (strchr(finger_keys[j], s[i])) {
                fingers[j]++;
                break;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        printf("%d\n", fingers[i]);
    }

    return 0;
}