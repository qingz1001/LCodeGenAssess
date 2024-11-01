#include <stdio.h>
#include <string.h>

void expand(int p1, int p2, int p3, char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '-' && i > 0 && i < len - 1) {
            char left = str[i - 1];
            char right = str[i + 1];
            if ((left >= 'a' && right >= 'a' && left <= 'z' && right <= 'z') ||
                (left >= '0' && right >= '0' && left <= '9' && right <= '9') &&
                (left < right)) {
                str[i] = '\0';
                char start = left;
                char end = right;
                if (p3 == 2) {
                    start = right;
                    end = left;
                }
                for (char j = start + 1; j < end; j++) {
                    for (int k = 0; k < p2; k++) {
                        if (p1 == 1) {
                            if (j >= 'a' && j <= 'z') {
                                printf("%c", j);
                            } else {
                                printf("%c", j - '0' + 'a' - '1');
                            }
                        } else if (p1 == 2) {
                            if (j >= 'a' && j <= 'z') {
                                printf("%c", j + 'A' - 'a');
                            } else {
                                printf("%c", j - '0' + 'A' - '1');
                            }
                        } else {
                            printf("*");
                        }
                    }
                }
            }
        } else {
            printf("%c", str[i]);
        }
    }
}

int main() {
    int p1, p2, p3;
    char str[101];
    scanf("%d%d%d", &p1, &p2, &p3);
    scanf("%s", str);
    expand(p1, p2, p3, str);
    return 0;
}