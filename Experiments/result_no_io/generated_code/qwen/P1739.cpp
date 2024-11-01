#include <stdio.h>
#include <string.h>

int main() {
    char expression[256];
    scanf("%s", expression);
    
    int stack[20];
    int top = -1;
    
    for (int i = 0; expression[i] != '@'; i++) {
        if (expression[i] == '(') {
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