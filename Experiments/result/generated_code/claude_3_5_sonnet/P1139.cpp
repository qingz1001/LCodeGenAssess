#include <stdio.h>
#include <string.h>

#define MAX_N 16

char input[MAX_N];
char stack[MAX_N];
int top = -1;
int n;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

char peek() {
    return stack[top];
}

void move(char train, char from, char to) {
    printf("%c %c %c\n", train, from, to);
}

int solve() {
    int input_idx = 0;
    int output_idx = 0;
    
    while (output_idx < n) {
        if (input_idx < n && input[input_idx] == input[n - 1 - output_idx]) {
            move(input[input_idx], 'A', 'D');
            input_idx++;
            output_idx++;
        } else if (top >= 0 && peek() == input[n - 1 - output_idx]) {
            move(pop(), 'B', 'D');
            output_idx++;
        } else if (input_idx < n) {
            move(input[input_idx], 'A', 'B');
            push(input[input_idx]);
            input_idx++;
        } else {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    scanf("%d", &n);
    scanf("%s", input);
    
    if (solve()) {
        // 成功调度
    } else {
        printf("NO\n");
    }
    
    return 0;
}