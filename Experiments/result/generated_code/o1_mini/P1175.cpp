#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 200
#define TOKEN_SIZE 20

typedef struct {
    char stack[MAX];
    int top;
} CharStack;

typedef struct {
    char tokens[MAX][TOKEN_SIZE];
    int count;
} TokenList;

// Initialize stack
void init_stack(CharStack *s) {
    s->top = -1;
}

// Push to stack
void push(CharStack *s, char c) {
    if(s->top < MAX-1){
        s->stack[++(s->top)] = c;
    }
}

// Pop from stack
char pop(CharStack *s) {
    if(s->top >=0 ){
        return s->stack[(s->top)--];
    }
    return '\0';
}

// Peek stack
char peek_stack(CharStack *s) {
    if(s->top >=0 ){
        return s->stack[s->top];
    }
    return '\0';
}

// Check if operator
int is_operator(char c){
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}

// Get precedence
int precedence(char op){
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

// Check right associativity
int is_right_associative(char op){
    return op == '^';
}

// Integer power
long long int_pow(long long base, long long exp){
    long long res = 1;
    while(exp >0){
        if(exp &1){
            res *= base;
        }
        base *= base;
        exp >>=1;
    }
    return res;
}

// Convert infix to postfix
void infix_to_postfix(char *infix, TokenList *postfix){
    CharStack op_stack;
    init_stack(&op_stack);
    int i=0, len = strlen(infix);
    postfix->count =0;
    while(i < len){
        char c = infix[i];
        if(isdigit(c)){
            // Operand
            char num[2];
            num[0] = c;
            num[1] = '\0';
            strcpy(postfix->tokens[postfix->count++], num);
            i++;
        }
        else if(c == '('){
            push(&op_stack, c);
            i++;
        }
        else if(c == ')'){
            while(op_stack.top != -1 && peek_stack(&op_stack) != '('){
                char top_op = pop(&op_stack);
                char op_str[2] = {top_op, '\0'};
                strcpy(postfix->tokens[postfix->count++], op_str);
            }
            if(op_stack.top != -1 && peek_stack(&op_stack) == '('){
                pop(&op_stack);
            }
            i++;
        }
        else if(is_operator(c)){
            while(op_stack.top != -1 && is_operator(peek_stack(&op_stack))){
                char top_op = peek_stack(&op_stack);
                if( (precedence(top_op) > precedence(c)) ||
                   (precedence(top_op) == precedence(c) && !is_right_associative(c)) ){
                    pop(&op_stack);
                    char op_str[2] = {top_op, '\0'};
                    strcpy(postfix->tokens[postfix->count++], op_str);
                }
                else{
                    break;
                }
            }
            push(&op_stack, c);
            i++;
        }
        else{
            // Ignore any other characters (though input is guaranteed)
            i++;
        }
    }
    while(op_stack.top != -1){
        char top_op = pop(&op_stack);
        if(top_op != '(' && top_op != ')'){
            char op_str[2] = {top_op, '\0'};
            strcpy(postfix->tokens[postfix->count++], op_str);
        }
    }
}

// Compute operation
long compute(long a, long b, char op){
    long res = 0;
    switch(op){
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
        case '^': res = int_pow(a, b); break;
    }
    return res;
}

int main(){
    char infix[105];
    fgets(infix, sizeof(infix), stdin);
    // Remove newline if any
    int len = strlen(infix);
    if(infix[len-1]=='\n') infix[len-1]='\0';
    TokenList postfix;
    infix_to_postfix(infix, &postfix);
    // Initialize tokens array
    TokenList current;
    current.count = postfix.count;
    for(int i=0;i<postfix.count;i++){
        strcpy(current.tokens[i], postfix.tokens[i]);
    }
    while(1){
        // Print current postfix expression
        for(int i=0;i<current.count;i++){
            printf("%s ", current.tokens[i]);
        }
        if(current.count >0){
            printf("\n");
        }
        if(current.count ==1){
            break;
        }
        // Find first operator
        int op_idx = -1;
        for(int i=0;i<current.count;i++){
            if(is_operator(current.tokens[i][0])){
                op_idx = i;
                break;
            }
        }
        if(op_idx == -1){
            break; // No operator found
        }
        // Get operands
        if(op_idx <2){
            // Not enough operands, but input is valid
            break;
        }
        char *op = current.tokens[op_idx];
        char *a_str = current.tokens[op_idx-2];
        char *b_str = current.tokens[op_idx-1];
        long a = atol(a_str);
        long b = atol(b_str);
        long res = compute(a, b, op[0]);
        // Convert result to string
        char res_str[20];
        sprintf(res_str, "%ld", res);
        // Replace a, b, op with res
        // Shift left from op_idx+1
        // Place res at op_idx-2
        strcpy(current.tokens[op_idx-2], res_str);
        // Shift tokens
        for(int i=op_idx-1;i<current.count-3;i++){
            strcpy(current.tokens[i], current.tokens[i+2]);
        }
        // Adjust count
        current.count = current.count -2;
    }
    return 0;
}