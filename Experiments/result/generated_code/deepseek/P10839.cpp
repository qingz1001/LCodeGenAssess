#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    char operators[3] = {'+', '-', '*'};
    int found = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int result;
            if (operators[i] == '+') {
                result = a + b;
            } else if (operators[i] == '-') {
                result = a - b;
            } else {
                result = a * b;
            }

            if (operators[j] == '+') {
                result += c;
            } else if (operators[j] == '-') {
                result -= c;
            } else {
                result *= c;
            }

            if (result == d) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }

    if (found) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}