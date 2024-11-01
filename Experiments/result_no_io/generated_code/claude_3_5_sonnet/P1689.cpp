#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000000

int main() {
    char equation[MAX_LEN];
    fgets(equation, MAX_LEN, stdin);

    int x = -1, y = -1, z = -1;
    char op;
    int len = strlen(equation);
    int num = 0;
    int pos = 0;

    for (int i = 0; i < len; i++) {
        if (isdigit(equation[i])) {
            num = num * 10 + (equation[i] - '0');
        } else if (equation[i] == '+' || equation[i] == '-') {
            if (pos == 0) x = num;
            else if (pos == 1) y = num;
            op = equation[i];
            num = 0;
            pos++;
        } else if (equation[i] == '=') {
            if (pos == 1) y = num;
            num = 0;
            pos++;
        } else if (equation[i] == '?') {
            if (pos == 0) x = -1;
            else if (pos == 1) y = -1;
            else z = -1;
            pos++;
        }
    }

    if (z == -1) z = num;

    if (x == -1) {
        if (op == '+') x = z - y;
        else x = z + y;
    } else if (y == -1) {
        if (op == '+') y = z - x;
        else y = x - z;
    } else {
        if (op == '+') z = x + y;
        else z = x - y;
    }

    printf("%d\n", x == -1 ? x : (y == -1 ? y : z));

    return 0;
}