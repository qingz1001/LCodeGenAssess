#include <stdio.h>
#include <string.h>

int main() {
    char s[51];
    int count[8] = {0};
    char fingers[8][13] = {
        "1QAZ", "2WSX", "3EDC", "4RFV5TGB",
        "6YHN7UJM", "8IK,", "9OL.", "0P;/-=[']\\"
    };
    
    scanf("%s", s);
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 8; j++) {
            if (strchr(fingers[j], s[i]) != NULL) {
                count[j]++;
                break;
            }
        }
    }
    
    for (int i = 0; i < 8; i++) {
        printf("%d\n", count[i]);
    }
    
    return 0;
}