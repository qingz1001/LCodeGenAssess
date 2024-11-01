#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 6
#define MAX_ROWS 64

typedef struct {
    char vars[MAX_N];
    char result;
} Row;

Row rows[MAX_ROWS];
int n;

void readInput() {
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); i++) {
        scanf("%s", rows[i].vars);
        scanf(" %c", &rows[i].result);
    }
}

void printExpression(char *expr) {
    printf("%s\n", expr);
}

void generateExpression(char *expr, int index, int *used) {
    if (index == n) {
        for (int i = 0; i < (1 << n); i++) {
            int match = 1;
            for (int j = 0; j < n; j++) {
                if ((rows[i].vars[j] == 'T' && used[j] == 0) ||
                    (rows[i].vars[j] == 'F' && used[j] == 1)) {
                    match = 0;
                    break;
                }
            }
            if (match && rows[i].result == 'F') {
                return;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i > 0) strcat(expr, "&");
            if (used[i] == 0) strcat(expr, "!");
            strcat(expr, "a");
        }
        return;
    }

    used[index] = 0;
    generateExpression(expr, index + 1, used);
    used[index] = 1;
    generateExpression(expr, index + 1, used);
}

int main() {
    readInput();
    char expr[1000] = "";
    int used[MAX_N] = {0};
    generateExpression(expr, 0, used);
    printExpression(expr);
    return 0;
}