#include <stdio.h>
#include <ctype.h>

int main(){
    char s[60005];
    scanf("%s", s);
    long long sum = 0;
    int op = 1;
    long long current = 0;
    for(int i = 0; s[i]; i++){
        if(isdigit(s[i])){
            current = current * 10 + (s[i] - '0');
        }
        else{
            sum += op * current;
            current = 0;
            if(s[i] == '+') op = 1;
            else op = -1;
        }
    }
    sum += op * current;
    printf("%lld\n", sum);
    return 0;
}