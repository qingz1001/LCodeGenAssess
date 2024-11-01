#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 200
#define MAX_TOKENS 200
#define MAX_TOKEN_LEN 20

typedef struct {
    char data[MAX];
    int top;
} CharStack;

void initStack(CharStack *s) {
    s->top = -1;
}

int isEmpty(CharStack *s) {
    return s->top == -1;
}

void push(CharStack *s, char c) {
    if(s->top < MAX-1){
        s->data[++(s->top)] = c;
    }
}

char pop(CharStack *s) {
    if(!isEmpty(s)){
        return s->data[(s->top)--];
    }
    return '#';
}

char peek(CharStack *s) {
    if(!isEmpty(s)){
        return s->data[s->top];
    }
    return '#';
}

int precedence_op(char op){
    switch(op){
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}

int is_right_assoc(char op){
    return op == '^';
}

int main(){
    char infix[MAX];
    fgets(infix, MAX, stdin);
    int len = strlen(infix);
    if(infix[len-1] == '\n') infix[len-1] = '\0';
    
    CharStack stack;
    initStack(&stack);
    char postfix[MAX];
    int p = 0;
    
    for(int i=0;i<strlen(infix);i++){
        char c = infix[i];
        if(isdigit(c)){
            postfix[p++] = c;
            postfix[p++] = ' ';
        }
        else if(c == '('){
            push(&stack, c);
        }
        else if(c == ')'){
            while(!isEmpty(&stack) && peek(&stack) != '('){
                postfix[p++] = pop(&stack);
                postfix[p++] = ' ';
            }
            if(!isEmpty(&stack)) pop(&stack);
        }
        else{
            while(!isEmpty(&stack)){
                char top_op = peek(&stack);
                if((precedence_op(top_op) > precedence_op(c)) ||
                   (precedence_op(top_op) == precedence_op(c) && !is_right_assoc(c)) ){
                    postfix[p++] = pop(&stack);
                    postfix[p++] = ' ';
                }
                else break;
            }
            push(&stack, c);
        }
    }
    while(!isEmpty(&stack)){
        postfix[p++] = pop(&stack);
        postfix[p++] = ' ';
    }
    postfix[p] = '\0';
    
    // Tokenize postfix
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int nt = 0;
    char *token = strtok(postfix, " ");
    while(token != NULL){
        strcpy(tokens[nt++], token);
        token = strtok(NULL, " ");
    }
    
    while(nt >1){
        int op_idx = -1;
        for(int i=0;i<nt;i++) {
            if( strchr("+-*/^", tokens[i][0]) && strlen(tokens[i]) ==1 ){
                op_idx = i;
                break;
            }
        }
        if(op_idx == -1) break;
        long a = atol(tokens[op_idx-2]);
        long b = atol(tokens[op_idx-1]);
        long res;
        switch(tokens[op_idx][0]){
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '*': res = a * b; break;
            case '/': res = a / b; break;
            case '^': {
                res = 1;
                for(int i=0;i<b;i++) res *= a;
                break;
            }
            default: res = 0;
        }
        // Shift tokens
        char res_str[MAX_TOKEN_LEN];
        sprintf(res_str, "%ld", res);
        // Replace tokens[op_idx-2] to tokens[op_idx] with res_str
        strcpy(tokens[op_idx-2], res_str);
        for(int i=op_idx-1;i<nt-2;i++) strcpy(tokens[i], tokens[i+2]);
        nt -=2;
        // Print current postfix
        for(int i=0;i<nt;i++) printf("%s ", tokens[i]);
        printf("\n");
    }
    return 0;
}