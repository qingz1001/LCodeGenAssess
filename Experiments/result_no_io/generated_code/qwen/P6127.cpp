#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 6
#define MAX_LEN (1 << MAX_N)

int n;
char truth_table[MAX_LEN][MAX_N + 2];
char variables[MAX_N];

void print_expression(char *expr) {
    printf("%s\n", expr);
}

void generate_vanilla_form(int index, char *current_expr) {
    if (index == n) {
        print_expression(current_expr);
        return;
    }
    current_expr[index] = '!';
    generate_vanilla_form(index + 1, current_expr);
    current_expr[index] = '&';
    generate_vanilla_form(index + 1, current_expr);
    current_expr[index] = '|';
    generate_vanilla_form(index + 1, current_expr);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < MAX_LEN; ++i) {
        scanf("%s", truth_table[i]);
        for (int j = 0; j < n; ++j) {
            variables[j] = 'a' + j;
        }
    }

    char expression[MAX_LEN * 2];
    memset(expression, '\0', sizeof(expression));
    generate_vanilla_form(0, expression);

    return 0;
}