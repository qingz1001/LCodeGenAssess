#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char s[101];
    scanf("%s", s);
    int stack[100];
    int top = -1;
    int i = 0;
    int len = strlen(s);
    while(i < len){
        if(isdigit(s[i])){
            int num = 0;
            while(i < len && isdigit(s[i])){
                num = num * 10 + (s[i] - '0');
                i++;
            }
            if(s[i] == '.'){
                i++;
            }
            stack[++top] = num;
        }
        else{
            char op = s[i];
            if(op == '@'){
                break;
            }
            int operand2 = stack[top--];
            int operand1 = stack[top--];
            int res;
            if(op == '+'){
                res = operand1 + operand2;
            }
            else if(op == '-'){
                res = operand1 - operand2;
            }
            else if(op == '*'){
                res = operand1 * operand2;
            }
            else if(op == '/'){
                res = operand1 / operand2;
            }
            stack[++top] = res;
            i++;
        }
    }
    printf("%d\n", stack[top]);
    return 0;
}