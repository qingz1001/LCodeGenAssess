#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int result;
    int found = 0;

    for (int op1 = 0; op1 < 3 && !found; op1++) {
        for (int op2 = 0; op2 < 3 && !found; op2++) {
            if (op1 == 0) {
                result = a + b;
            } else if (op1 == 1) {
                result = a - b;
            } else {
                result = a * b;
            }

            if (op2 == 0) {
                result += c;
            } else if (op2 == 1) {
                result -= c;
            } else {
                result *= c;
            }

            if (result == d) {
                found = 1;
            }
        }
    }

    if (found) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}