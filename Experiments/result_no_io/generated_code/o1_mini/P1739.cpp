#include <stdio.h>

int main(){
    char c;
    int stack[20];
    int top = 0;
    while((c = getchar()) != '@' && c != EOF){
        if(c == '('){
            if(top < 20){
                stack[top++] = 1;
            }
            else{
                // Exceeds stack size, but constraints ensure this won't happen
            }
        }
        else if(c == ')'){
            if(top > 0){
                top--;
            }
            else{
                printf("NO");
                return 0;
            }
        }
    }
    if(top == 0)
        printf("YES");
    else
        printf("NO");
    return 0;
}