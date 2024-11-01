#include <stdio.h>

int main() {
    char title[6];
    int count = 0;
    scanf("%s", title);
    for (int i = 0; title[i] != '\0'; i++) {
        if (title[i] != ' ' && title[i] != '\n') {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}