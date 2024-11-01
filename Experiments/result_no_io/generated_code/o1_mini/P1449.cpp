#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long stack[100];
int top = -1;

void push(long long x) {
    stack[++top] = x;
}

long long pop() {
    return stack[top--];
}

int main(){
    char s[101];
    scanf("%s", s);
    int len = strlen(s);
    int i = 0;
    while(i < len){
        if(isdigit(s[i]) || (s[i] == '-' && isdigit(s[i+1]))){
            int start = i;
            while(s[i] != '.' && i < len){
                i++;
            }
            char numStr[20];
            int j = 0;
            for(int k = start; k < i; k++) numStr[j++] = s[k];
            numStr[j] = '\0';
            long long num = 0;
            int sign = 1;
            int idx = 0;
            if(numStr[0] == '-'){
                sign = -1;
                idx = 1;
            }
            while(numStr[idx]){
                num = num *10 + (numStr[idx]-'0');
                idx++;
            }
            num *= sign;
            push(num);
            i++; // skip '.'
        }
        else{
            if(s[i] == '@') break;
            long long b = pop();
            long long a = pop();
            long long res;
            switch(s[i]){
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            push(res);
            i++;
        }
    }
    printf("%lld", stack[top]);
}