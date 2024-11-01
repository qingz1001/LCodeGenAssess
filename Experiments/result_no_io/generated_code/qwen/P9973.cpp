#include <stdio.h>
#include <string.h>

int main() {
    char s[201];
    scanf("%s", s);
    if (strlen(s) >= 19 && strncmp(s, "AI", 2) == 0) {
        printf("AI\n");
    } else {
        printf("Human\n");
    }
    return 0;
}