#include <stdio.h>
#include <string.h>

int main() {
    char equation[1000001];
    scanf("%s", equation);

    int x, y, z;
    char op;

    if (sscanf(equation, "%d+%d=%d", &x, &y, &z) == 3) {
        printf("%d\n", z - x - y);
    } else if (sscanf(equation, "%d-%d=%d", &x, &y, &z) == 3) {
        printf("%d\n", x - y - z);
    } else if (sscanf(equation, "%d+%d=?", &x, &y) == 2) {
        printf("%d\n", z - x - y);
    } else if (sscanf(equation, "%d-%d=?", &x, &y) == 2) {
        printf("%d\n", x - y - z);
    } else if (sscanf(equation, "?+%d=%d", &y, &z) == 2) {
        printf("%d\n", z - y - x);
    } else if (sscanf(equation, "?-%d=%d", &y, &z) == 2) {
        printf("%d\n", z + y - x);
    }

    return 0;
}