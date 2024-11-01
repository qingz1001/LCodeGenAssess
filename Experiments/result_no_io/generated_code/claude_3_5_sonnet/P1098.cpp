#include <stdio.h>
#include <string.h>
#include <ctype.h>

void expand(char *s, int p1, int p2, int p3) {
    int len = strlen(s);
    char result[1000] = "";
    int r = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '-' && i > 0 && i < len - 1) {
            char left = s[i-1], right = s[i+1];
            if ((isalpha(left) && isalpha(right) && left < right) ||
                (isdigit(left) && isdigit(right) && left < right)) {
                
                if (right == left + 1) {
                    result[r++] = left;
                    result[r++] = right;
                    i++;
                    continue;
                }

                result[r++] = left;
                for (char c = left + 1; c < right; c++) {
                    char fill;
                    if (p1 == 1) fill = islower(c) ? c : tolower(c);
                    else if (p1 == 2) fill = isupper(c) ? c : toupper(c);
                    else fill = '*';

                    for (int j = 0; j < p2; j++) {
                        if (p3 == 1)
                            result[r++] = fill;
                        else
                            result[r++] = right - (c - left);
                    }
                }
                result[r++] = right;
                i++;
            } else {
                result[r++] = s[i-1];
                result[r++] = s[i];
            }
        } else {
            result[r++] = s[i];
        }
    }
    result[r] = '\0';
    printf("%s\n", result);
}

int main() {
    int p1, p2, p3;
    char s[101];
    
    scanf("%d %d %d", &p1, &p2, &p3);
    scanf("%s", s);

    expand(s, p1, p2, p3);

    return 0;
}