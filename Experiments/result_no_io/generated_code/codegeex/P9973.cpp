#include <stdio.h>
#include <string.h>

int main() {
    char s[201];
    scanf("%s", s);

    int len = strlen(s);
    if (len > 19) {
        printf("AI\n");
    } else {
        printf("Human\n");
    }

    return 0;
}