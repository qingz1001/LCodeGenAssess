#include <stdio.h>
#include <string.h>

void splitNumber(char *num) {
    int len = strlen(num);
    if (len == 1) {
        printf("%s", num);
        return;
    }

    for (int i = len - 1; i > 0; i--) {
        char part1[501];
        char part2[501];
        strncpy(part1, num, i);
        part1[i] = '\0';
        strcpy(part2, num + i);

        if (strcmp(part1, part2) >= 0) {
            printf("%s,%s", part1, part2);
            return;
        }
    }
}

int main() {
    char num[501];
    scanf("%s", num);
    splitNumber(num);
    return 0;
}