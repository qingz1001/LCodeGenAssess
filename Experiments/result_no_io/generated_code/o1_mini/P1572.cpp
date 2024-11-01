#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd_func(int a, int b){
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    while(b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(){
    char s[201];
    fgets(s, sizeof(s), stdin);
    int len = strlen(s);
    if(s[len-1] == '\n') s[len-1] = '\0';
    int num = 0, den = 1;
    int i = 0;
    while(i < strlen(s)){
        int sign = 1;
        if(s[i] == '+'){
            sign = 1;
            i++;
        }
        else if(s[i] == '-'){
            sign = -1;
            i++;
        }
        int current_num = 0, current_den = 0;
        // Parse numerator
        if(s[i] == '-'){
            sign *= -1;
            i++;
        }
        while(i < strlen(s) && s[i] >= '0' && s[i] <= '9'){
            current_num = current_num * 10 + (s[i] - '0');
            i++;
        }
        current_num *= sign;
        if(s[i] == '/'){
            i++;
        }
        // Parse denominator
        while(i < strlen(s) && s[i] >= '0' && s[i] <= '9'){
            current_den = current_den * 10 + (s[i] - '0');
            i++;
        }
        // Add fractions: num/den + current_num/current_den
        num = num * current_den + current_num * den;
        den = den * current_den;
        // Simplify
        int g = gcd_func(num, den);
        num /= g;
        den /= g;
    }
    if(den == 1){
        printf("%d\n", num);
    }
    else{
        printf("%d/%d\n", num, den);
    }
    return 0;
}