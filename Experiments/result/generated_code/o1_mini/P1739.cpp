#include <stdio.h>

int main(){
    char expr[256];
    int stack[20];
    int top = -1;
    int i=0;
    if(scanf("%255s", expr)!=1){
        printf("NO");
        return 0;
    }
    while(expr[i] != '@' && expr[i] != '\0'){
        if(expr[i] == '('){
            if(top >=19){
                printf("NO");
                return 0;
            }
            stack[++top] = '(';
        }
        else if(expr[i] == ')'){
            if(top <0){
                printf("NO");
                return 0;
            }
            top--;
        }
        i++;
    }
    if(expr[i] == '@' && top == -1){
        printf("YES");
    }
    else{
        printf("NO");
    }
    return 0;
}