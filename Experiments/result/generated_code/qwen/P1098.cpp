#include <stdio.h>
#include <string.h>

void expand(char *str, int p1, int p2, int p3) {
    char temp[101];
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i + 1] == '-' && ((str[i] >= 'a' && str[i + 2] <= 'z') || (str[i] >= 'A' && str[i + 2] <= 'Z'))) {
            char start = str[i], end = str[i + 2];
            i += 3;
            if (start == end - 1) continue;
            for (char c = start; c < end; c++) {
                for (int k = 0; k < p2; k++) {
                    temp[j++] = c;
                }
            }
        } else {
            temp[j++] = str[i++];
        }
    }
    temp[j] = '\0';
    if (p3 == 2) {
        for (i = 0, j = strlen(temp) - 1; i < j; i++, j--) {
            char t = temp[i];
            temp[i] = temp[j];
            temp[j] = t;
        }
    }
    printf("%s\n", temp);
}

int main() {
    int p1, p2, p3;
    scanf("%d %d %d", &p1, &p2, &p3);
    getchar(); // consume the newline character
    char str[101];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // remove the newline character at the end of the string
    expand(str, p1, p2, p3);
    return 0;
}