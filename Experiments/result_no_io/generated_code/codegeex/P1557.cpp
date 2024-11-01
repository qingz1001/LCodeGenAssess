#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2000

typedef struct {
    int sign;
    int multiplier;
    int value;
} Term;

Term terms[MAX_SIZE];
int term_count = 0;

void parse_expression(const char *expression) {
    int i = 0;
    while (expression[i] != '\0') {
        Term term;
        term.sign = 1;
        term.multiplier = 1;
        term.value = 0;

        // Handle sign
        if (expression[i] == '+') {
            term.sign = 1;
            i++;
        } else if (expression[i] == '-') {
            term.sign = -1;
            i++;
        }

        // Handle multiplier
        if (expression[i] == '(') {
            i++;
            while (expression[i] != ')') {
                term.multiplier = term.multiplier * 10 + (expression[i] - '0');
                i++;
            }
            i++;
        }

        // Handle value
        while (expression[i] >= '0' && expression[i] <= '9') {
            term.value = term.value * 10 + (expression[i] - '0');
            i++;
        }

        // Store the term
        terms[term_count++] = term;
    }
}

int calculate() {
    int result = 0;
    for (int i = 0; i < term_count; i++) {
        result += terms[i].sign * terms[i].multiplier * terms[i].value;
    }
    return result;
}

int main() {
    char expression[MAX_SIZE];
    fgets(expression, MAX_SIZE, stdin);

    // Remove the newline character if present
    expression[strcspn(expression, "\n")] = 0;

    parse_expression(expression);
    int result = calculate();

    printf("%d\n", result);
    return 0;
}