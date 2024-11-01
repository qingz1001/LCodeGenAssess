#include <stdio.h>
#include <string.h>

int main() {
    char s[201];
    fgets(s, sizeof(s), stdin);

    if (strncmp(s, "You are right, but ", 19) == 0) {
        printf("AI\n");
    } else {
        printf("Human\n");
    }

    return 0;
}