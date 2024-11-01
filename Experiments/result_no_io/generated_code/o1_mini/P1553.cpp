#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to reverse a string in place
void reverse_str(char *str) {
    int len = strlen(str);
    int i;
    for(i=0;i<len/2;i++) {
        char tmp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = tmp;
    }
}

// Function to remove leading zeros, keep at least one digit
void remove_leading_zeros(char *str) {
    int len = strlen(str);
    int i = 0;
    while(i < len-1 && str[i] == '0') i++;
    if(i > 0) {
        memmove(str, str+i, len-i+1);
    }
}

// Function to remove trailing zeros, keep one if all zeros
void remove_trailing_zeros(char *str) {
    int len = strlen(str);
    if(len == 0) return;
    int i = len-1;
    while(i >0 && str[i] == '0') i--;
    if(str[i] == '.') i--;
    str[i+1] = '\0';
}

int main(){
    char s[100];
    scanf("%s",s);
    int len = strlen(s);
    if(strchr(s, '/')){
        // Fraction
        char num[50], den[50];
        sscanf(s, "%[^/]/%s", num, den);
        reverse_str(num);
        reverse_str(den);
        remove_leading_zeros(num);
        remove_leading_zeros(den);
        printf("%s/%s", num, den);
    }
    else if(strchr(s, '.')){
        // Decimal
        char intp[50], decp[50];
        sscanf(s, "%[^.].%s", intp, decp);
        reverse_str(intp);
        reverse_str(decp);
        remove_leading_zeros(intp);
        remove_trailing_zeros(decp);
        printf("%s.%s", intp, decp);
    }
    else if(strchr(s, '%')){
        // Percentage
        char num[50];
        sscanf(s, "%[^%]%%", num);
        reverse_str(num);
        remove_leading_zeros(num);
        printf("%s%%", num);
    }
    else{
        // Integer
        reverse_str(s);
        remove_leading_zeros(s);
        printf("%s", s);
    }
    return 0;
}