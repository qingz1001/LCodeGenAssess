#include <stdio.h>
#include <string.h>

int main() {
    char equation[1000];
    scanf("%s", equation);

    int len = strlen(equation);
    int x_pos = -1;
    int sign = 1;
    int sum = 0;
    int num = 0;

    for (int i = 0; i < len; i++) {
        if (equation[i] == 'x') {
            x_pos = i;
            break;
        } else if (equation[i] == '+') {
            sign = 1;
        } else if (equation[i] == '-') {
            sign = -1;
        } else if (equation[i] >= '0' && equation[i] <= '9') {
            num = num * 10 + (equation[i] - '0');
        } else if (equation[i] == '=') {
            sum += sign * num;
            num = 0;
            sign = 1;
        }
    }

    sum += sign * num;

    if (x_pos == -1) {
        printf("No variable x found\n");
    } else {
        double result = (double)sum / (equation[x_pos - 1] == '-' ? -1 : 1);
        printf("%.3f\n", result);
    }

    return 0;
}