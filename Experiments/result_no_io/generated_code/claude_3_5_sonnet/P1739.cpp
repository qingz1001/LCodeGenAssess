#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 255
#define MAX_LEFT_BRACKETS 20

int main() {
    char expression[MAX_LENGTH];
    int stack[MAX_LEFT_BRACKETS];
    int top = -1;
    int i;

    fgets(expression, MAX_LENGTH, stdin);

    for (i = 0; expression[i] != '@' && expression[i] != '\0' && expression[i] != '\n'; i++) {
        if (expression[i] == '(') {
            if (top >= MAX_LEFT_BRACKETS - 1) {
                printf("NO\n");
                return 0;
            }
            stack[++top] = i;
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