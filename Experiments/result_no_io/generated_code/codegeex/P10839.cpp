#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);

    // Check all possible combinations of operations
    if ((a + b) + c == d || (a + b) * c == d || (a + b) - c == d ||
        (a * b) + c == d || (a * b) * c == d || (a * b) - c == d ||
        (a - b) + c == d || (a - b) * c == d || (a - b) - c == d) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}