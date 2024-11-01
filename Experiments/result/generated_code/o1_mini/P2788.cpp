#include <stdio.h>
#include <ctype.h>

int main(){
    char s[60001];
    scanf("%s", s);
    long long res = 0;
    int i = 0;
    char op = '+';
    while (s[i]){
        if (s[i] == '+' || s[i] == '-'){
            op = s[i++];
        }
        int num = 0;
        while (s[i] && isdigit(s[i])){
            num = num * 10 + (s[i++] - '0');
        }
        if (op == '+') res += num;
        else res -= num;
    }
    printf("%lld\n", res);
}