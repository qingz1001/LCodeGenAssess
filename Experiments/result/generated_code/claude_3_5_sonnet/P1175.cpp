#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LEN 100

char infix[MAX_LEN], postfix[MAX_LEN];
char stack[MAX_LEN];
int top = -1;

int precedence(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return 0;
}

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

void infix_to_postfix() {
    int i, j = 0;
    char c;

    for(i = 0; infix[i] != '\0'; i++) {
        if(isdigit(infix[i])) {
            postfix[j++] = infix[i];
            postfix[j++] = ' ';
        }
        else if(infix[i] == '(') {
            push(infix[i]);
        }
        else if(infix[i] == ')') {
            while((c = pop()) != '(') {
                postfix[j++] = c;
                postfix[j++] = ' ';
            }
        }
        else {
            while(top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                if(infix[i] == '^' && stack[top] == '^') break;
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            push(infix[i]);
        }
    }

    while(top != -1) {
        postfix[j++] = pop();
        postfix[j++] = ' ';
    }
    postfix[j-1] = '\0';
}

long long evaluate() {
    long long stack[MAX_LEN], a, b;
    int top = -1, i;

    for(i = 0; postfix[i] != '\0'; i++) {
        if(isdigit(postfix[i])) {
            stack[++top] = postfix[i] - '0';
        }
        else if(postfix[i] != ' ') {
            b = stack[top--];
            a = stack[top--];
            switch(postfix[i]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
                case '^': stack[++top] = pow(a, b); break;
            }
        }
    }
    return stack[top];
}

void print_steps() {
    char temp[MAX_LEN];
    strcpy(temp, postfix);
    printf("%s\n", temp);

    while(1) {
        int i, j = 0, flag = 0;
        for(i = 0; temp[i] != '\0'; i++) {
            if(isdigit(temp[i]) || temp[i] == ' ') {
                temp[j++] = temp[i];
            }
            else {
                long long a = 0, b = 0;
                while(j > 0 && temp[j-1] == ' ') j--;
                while(j > 0 && isdigit(temp[j-1])) {
                    b = b * 10 + (temp[--j] - '0');
                }
                while(j > 0 && temp[j-1] == ' ') j--;
                while(j > 0 && isdigit(temp[j-1])) {
                    a = a * 10 + (temp[--j] - '0');
                }
                long long result;
                switch(temp[i]) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': result = a / b; break;
                    case '^': result = pow(a, b); break;
                }
                j += sprintf(&temp[j], "%lld ", result);
                flag = 1;
                break;
            }
        }
        temp[j] = '\0';
        if(!flag) break;
        printf("%s\n", temp);
    }
}

int main() {
    scanf("%s", infix);
    infix_to_postfix();
    print_steps();
    return 0;
}