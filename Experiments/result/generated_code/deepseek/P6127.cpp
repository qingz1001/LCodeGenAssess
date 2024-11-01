#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 6
#define MAX_ROWS (1 << MAX_N)

typedef struct {
    char vars[MAX_N];
    char result;
} Row;

typedef struct {
    char expr[1000];
    int len;
} Expression;

Row rows[MAX_ROWS];
int n;

void read_input() {
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); i++) {
        scanf("%s", rows[i].vars);
        rows[i].result = rows[i].vars[n];
        rows[i].vars[n] = '\0';
    }
}

void generate_expression(Expression *expr, char *vars, char result) {
    char temp[1000];
    int len = 0;
    for (int i = 0; i < n; i++) {
        if (vars[i] == 'T') {
            if (len > 0) {
                temp[len++] = '&';
            }
            temp[len++] = 'a' + i;
        } else {
            if (len > 0) {
                temp[len++] = '&';
            }
            temp[len++] = '!';
            temp[len++] = 'a' + i;
        }
    }
    temp[len] = '\0';

    if (result == 'T') {
        if (expr->len > 0) {
            expr->expr[expr->len++] = '|';
        }
        strcpy(expr->expr + expr->len, temp);
        expr->len += len;
    }
}

void find_shortest_expression(Expression *expr) {
    expr->len = 0;
    for (int i = 0; i < (1 << n); i++) {
        if (rows[i].result == 'T') {
            generate_expression(expr, rows[i].vars, rows[i].result);
        }
    }
    expr->expr[expr->len] = '\0';
}

int main() {
    read_input();
    Expression expr;
    find_shortest_expression(&expr);
    printf("%s\n", expr.expr);
    return 0;
}