#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    double coef;
    double const_term;
} Side;

Side parse_side(char *expr, char var) {
    Side side = {0.0, 0.0};
    int len = strlen(expr);
    int i = 0;
    int sign = 1;
    while (i < len) {
        // Determine the sign
        if (expr[i] == '+') {
            sign = 1;
            i++;
        }
        else if (expr[i] == '-') {
            sign = -1;
            i++;
        }

        // Parse the number
        double num = 0.0;
        int has_num = 0;
        while (i < len && isdigit(expr[i])) {
            has_num = 1;
            num = num * 10 + (expr[i] - '0');
            i++;
        }

        // Check if it's a variable term
        if (i < len && expr[i] == var) {
            if (!has_num) num = 1.0;
            side.coef += sign * num;
            i++; // skip variable
        }
        else {
            side.const_term += sign * num;
        }
    }
    return side;
}

int main() {
    char equation[1005];
    scanf("%s", equation);
    int len = strlen(equation);
    int eq_pos = -1;
    char var = '\0';
    for(int i=0;i<len;i++) {
        if(equation[i] == '=') {
            eq_pos = i;
            break;
        }
        if(isalpha(equation[i])) {
            var = equation[i];
        }
    }
    char left[1005];
    char right[1005];
    strncpy(left, equation, eq_pos);
    left[eq_pos] = '\0';
    strcpy(right, equation + eq_pos + 1);
    Side side_left = parse_side(left, var);
    Side side_right = parse_side(right, var);
    double A = side_left.coef;
    double B = side_left.const_term;
    double C = side_right.coef;
    double D = side_right.const_term;
    double numerator = D - B;
    double denominator = A - C;
    double result = numerator / denominator;
    printf("%.3lf\n", result);
    return 0;
}