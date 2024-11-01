#include <stdio.h>

int main() {
    char ch;
    int count = 0, prev = 0, first = 1;
    scanf("%c", &ch);

    while (ch != '\n') {
        count++;
        if (ch != prev) {
            if (!first) {
                printf(" %d", count);
            } else {
                printf("%d", count);
                first = 0;
            }
            prev = ch;
            count = 0;
        }
        ch = getchar();
    }
    printf(" %d\n", count);

    return 0;
}