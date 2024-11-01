#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 9

char ops[MAXN];
int N;

void evaluate(char *expr) {
    int sum = 0;
    int num = 0;
    char last_op = '+';

    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] >= '0' && expr[i] <= '9') {
            num = num * 10 + (expr[i] - '0');
        } else {
            if (last_op == '+') {
                sum += num;
            } else {
                sum -= num;
            }
            num = 0;
            last_op = expr[i];
        }
    }

    if (last_op == '+') {
        sum += num;
    } else {
        sum -= num;
    }

    if (sum == 0) {
        printf("%s\n", expr);
    }
}

void generate(int pos) {
    if (pos == N - 1) {
        char expr[2 * MAXN];
        int idx = 0;
        for (int i = 0; i < N - 1; i++) {
            expr[idx++] = '1' + i;
            if (ops[i] != ' ') {
                expr[idx++] = ops[i];
            }
        }
        expr[idx++] = '1' + N - 1;
        expr[idx] = '\0';
        evaluate(expr);
        return;
    }

    ops[pos] = ' ';
    generate(pos + 1);
    ops[pos] = '+';
    generate(pos + 1);
    ops[pos] = '-';
    generate(pos + 1);
}

int main() {
    scanf("%d", &N);
    generate(0);
    return 0;
}