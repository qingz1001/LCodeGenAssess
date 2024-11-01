#include <stdio.h>

int main() {
    int a, b, c, d;
    int p, m, g;

    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);

    char result[3][6];
    const char* none = "none";
    const char* one = "one";
    const char* both = "both";

    for (int i = 0; i < 3; i++) {
        if ((i == 0 && (p % (a + b) < a)) || (i == 1 && (m % (c + d) < c)) || (i == 2 && (g % (a + b) < a))) {
            if (result[i - 1][0] != '\0') {
                strcpy(result[i], both);
            } else {
                strcpy(result[i], one);
            }
        } else {
            strcpy(result[i], none);
        }
    }

    printf("%s\n%s\n%s\n", result[0], result[1], result[2]);

    return 0;
}