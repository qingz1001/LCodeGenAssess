#include <stdio.h>
#include <string.h>
#include <ctype.h>

void expand(char *s, int p1, int p2, int p3) {
    int len = strlen(s);
    char result[1000] = "";
    int k = 0;

    for (int i = 0; i < len; i++) {
        if (i + 2 < len && s[i+1] == '-' && 
            ((islower(s[i]) && islower(s[i+2]) && s[i] < s[i+2]) ||
             (isdigit(s[i]) && isdigit(s[i+2]) && s[i] < s[i+2]))) {
            
            result[k++] = s[i];
            
            if (s[i+2] == s[i] + 1) {
                result[k++] = s[i+2];
                i += 2;
                continue;
            }

            for (char c = s[i] + 1; c < s[i+2]; c++) {
                for (int j = 0; j < p2; j++) {
                    if (p1 == 1) result[k++] = islower(s[i]) ? c : c;
                    else if (p1 == 2) result[k++] = islower(s[i]) ? toupper(c) : c;
                    else result[k++] = '*';
                }
            }

            if (p3 == 2) {
                int start = k - (s[i+2] - s[i] - 1) * p2;
                int end = k - 1;
                while (start < end) {
                    char temp = result[start];
                    result[start] = result[end];
                    result[end] = temp;
                    start++;
                    end--;
                }
            }

            result[k++] = s[i+2];
            i += 2;
        } else {
            result[k++] = s[i];
        }
    }
    result[k] = '\0';
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