#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 55
#define MAX_STACK 100

typedef struct {
    int coef[11];
} Polynomial;

char expr[MAX_LEN];
char stack[MAX_STACK];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    if (op == '^') return 3;
    return 0;
}

Polynomial evaluate(char *expr) {
    Polynomial result = {0};
    Polynomial operands[MAX_STACK];
    int operand_top = -1;
    char *token = strtok(expr, " ");
    
    while (token) {
        if (isdigit(token[0])) {
            Polynomial p = {0};
            p.coef[0] = atoi(token);
            operands[++operand_top] = p;
        } else if (token[0] == 'a') {
            Polynomial p = {0};
            p.coef[1] = 1;
            operands[++operand_top] = p;
        } else {
            Polynomial b = operands[operand_top--];
            Polynomial a = operands[operand_top--];
            Polynomial res = {0};
            
            switch(token[0]) {
                case '+':
                    for (int i = 0; i <= 10; i++) res.coef[i] = a.coef[i] + b.coef[i];
                    break;
                case '-':
                    for (int i = 0; i <= 10; i++) res.coef[i] = a.coef[i] - b.coef[i];
                    break;
                case '*':
                    for (int i = 0; i <= 5; i++)
                        for (int j = 0; j <= 5; j++)
                            if (i + j <= 10) res.coef[i+j] += a.coef[i] * b.coef[j];
                    break;
                case '^':
                    if (b.coef[0] >= 1 && b.coef[0] <= 10) {
                        res = a;
                        for (int i = 1; i < b.coef[0]; i++) {
                            Polynomial temp = {0};
                            for (int j = 0; j <= 5; j++)
                                for (int k = 0; k <= 5; k++)
                                    if (j + k <= 10) temp.coef[j+k] += res.coef[j] * a.coef[k];
                            res = temp;
                        }
                    }
                    break;
            }
            operands[++operand_top] = res;
        }
        token = strtok(NULL, " ");
    }
    return operands[operand_top];
}

void infix_to_postfix(char *infix, char *postfix) {
    char *token = strtok(infix, " ");
    int pos = 0;
    
    while (token) {
        if (isdigit(token[0]) || token[0] == 'a') {
            strcpy(postfix + pos, token);
            pos += strlen(token);
            postfix[pos++] = ' ';
        } else if (token[0] == '(') {
            push(token[0]);
        } else if (token[0] == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[pos++] = pop();
                postfix[pos++] = ' ';
            }
            if (top >= 0 && stack[top] == '(') pop();
        } else {
            while (top >= 0 && precedence(stack[top]) >= precedence(token[0])) {
                postfix[pos++] = pop();
                postfix[pos++] = ' ';
            }
            push(token[0]);
        }
        token = strtok(NULL, " ");
    }
    
    while (top >= 0) {
        postfix[pos++] = pop();
        postfix[pos++] = ' ';
    }
    postfix[pos] = '\0';
}

int are_equivalent(Polynomial p1, Polynomial p2) {
    for (int i = 0; i <= 10; i++) {
        if (p1.coef[i] != p2.coef[i]) return 0;
    }
    return 1;
}

int main() {
    char standard_expr[MAX_LEN], option_expr[MAX_LEN];
    char postfix_standard[MAX_LEN * 2], postfix_option[MAX_LEN * 2];
    int n;
    
    fgets(standard_expr, MAX_LEN, stdin);
    standard_expr[strcspn(standard_expr, "\n")] = 0;
    infix_to_postfix(standard_expr, postfix_standard);
    Polynomial standard_poly = evaluate(postfix_standard);
    
    scanf("%d\n", &n);
    
    for (char option = 'A'; option < 'A' + n; option++) {
        fgets(option_expr, MAX_LEN, stdin);
        option_expr[strcspn(option_expr, "\n")] = 0;
        infix_to_postfix(option_expr, postfix_option);
        Polynomial option_poly = evaluate(postfix_option);
        
        if (are_equivalent(standard_poly, option_poly)) {
            printf("%c", option);
        }
    }
    printf("\n");
    
    return 0;
}