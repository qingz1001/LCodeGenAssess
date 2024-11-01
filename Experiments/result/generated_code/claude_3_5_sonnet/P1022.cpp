#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

void parse_equation(char *eq, double *a, double *b) {
    int i, sign = 1, left = 1;
    *a = 0; *b = 0;
    char num[MAX_LEN] = {0};
    int num_len = 0;

    for (i = 0; eq[i]; i++) {
        if (eq[i] >= 'a' && eq[i] <= 'z') {
            if (num_len == 0) {
                *a += sign * (left ? 1 : -1);
            } else {
                *a += sign * (left ? 1 : -1) * atof(num);
                num_len = 0;
            }
        } else if (eq[i] == '+' || eq[i] == '-' || eq[i] == '=') {
            if (num_len > 0) {
                *b += sign * (left ? -1 : 1) * atof(num);
                num_len = 0;
            }
            if (eq[i] == '=') {
                left = 0;
                sign = 1;
            } else {
                sign = (eq[i] == '+') ? 1 : -1;
            }
        } else if (eq[i] >= '0' && eq[i] <= '9' || eq[i] == '.') {
            num[num_len++] = eq[i];
            num[num_len] = '\0';
        }
    }
    
    if (num_len > 0) {
        *b += sign * (left ? -1 : 1) * atof(num);
    }
}

int main() {
    char equation[MAX_LEN];
    double a = 0, b = 0;
    
    fgets(equation, MAX_LEN, stdin);
    equation[strcspn(equation, "\n")] = 0;
    
    parse_equation(equation, &a, &b);
    
    if (a == 0) {
        printf("No solution\n");
    } else {
        double x = b / a;
        printf("%c=%.3f\n", equation[strcspn(equation, "abcdefghijklmnopqrstuvwxyz")], x);
    }
    
    return 0;
}