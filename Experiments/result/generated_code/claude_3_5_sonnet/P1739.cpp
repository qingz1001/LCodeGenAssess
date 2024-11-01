#include <stdio.h>
#include <string.h>

#define MAX_LEN 255
#define MAX_LEFT_BRACKETS 20

int main() {
    char expression[MAX_LEN];
    char stack[MAX_LEFT_BRACKETS];
    int top = -1;
    int i;

    scanf("%s", expression);

    for (i = 0; expression[i] != '@' && i < MAX_LEN; i++) {
        if (expression[i] == '(') {
            if (top >= MAX_LEFT_BRACKETS - 1) {
                printf("NO\n");
                return 0;
            }
            stack[++top] = '(';
        } else if (expression[i] == ')') {
            if (top == -1) {
                printf("NO\n");
                return 0;
            }
            top--;
        }
    }

    if (top == -1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}