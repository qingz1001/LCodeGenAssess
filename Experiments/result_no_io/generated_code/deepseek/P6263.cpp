#include <stdio.h>
#include <string.h>

int main() {
    char s[51];
    int fingers[8] = {0}; // 8 fingers excluding the thumb
    const char *finger_keys[8] = {
        "12345qwertasdfgzxcvb", // Left pinky to left thumb
        "67890yuiophjkl;nm,./", // Right thumb to right pinky
        "1qaz", // Left pinky
        "2wsx", // Left ring
        "3edc", // Left middle
        "4rfv5tgb", // Left index
        "6yhn7ujm", // Right index
        "8ik,9ol.0p;/" // Right middle to right pinky
    };

    scanf("%s", s);
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
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