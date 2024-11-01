#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to reverse a string in place
void reverse_str(char *str) {
    int len = strlen(str);
    int i=0, j=len-1;
    while(i < j){
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

// Function to remove leading zeros, keep at least one digit
void remove_leading_zeros(char *str){
    int len = strlen(str);
    int i=0;
    while(i < len-1 && str[i]=='0') i++;
    if(i >0){
        memmove(str, str+i, len-i+1);
    }
}

// Function to remove trailing zeros, keep one zero if all zeros
void remove_trailing_zeros(char *str){
    int len = strlen(str);
    int i = len-1;
    while(i >0 && str[i]=='0') i--;
    if(str[i] != '0') {
        str[i+1] = '\0';
    }
    else{
        str[1] = '\0';
    }
}

int main(){
    char s[100];
    scanf("%s", s);
    int len = strlen(s);
    if(s[len-1] == '%'){
        // Percentage
        s[len-1] = '\0';
        reverse_str(s);
        remove_leading_zeros(s);
        printf("%s%%", s);
    }
    else{
        char *slash = strchr(s, '/');
        if(slash){
            // Fraction
            *slash = '\0';
            char numerator[100], denominator[100];
            strcpy(numerator, s);
            strcpy(denominator, slash+1);
            reverse_str(numerator);
            reverse_str(denominator);
            remove_leading_zeros(numerator);
            remove_leading_zeros(denominator);
            printf("%s/%s", numerator, denominator);
        }
        else{
            char *dot = strchr(s, '.');
            if(dot){
                // Decimal
                *dot = '\0';
                char int_part[100], frac_part[100];
                strcpy(int_part, s);
                strcpy(frac_part, dot+1);
                reverse_str(int_part);
                reverse_str(frac_part);
                remove_leading_zeros(int_part);
                remove_trailing_zeros(frac_part);
                printf("%s.%s", int_part, frac_part);
            }
            else{
                // Integer
                reverse_str(s);
                remove_leading_zeros(s);
                printf("%s", s);
            }
        }
    }
    return 0;
}