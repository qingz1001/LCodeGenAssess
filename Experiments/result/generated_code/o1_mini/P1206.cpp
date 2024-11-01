#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGITS 100

// Function to convert a number to base B string
void convert_to_base(long num, int B, char* str){
    char temp[MAX_DIGITS];
    int idx = 0;
    if(num == 0){
        temp[idx++] = '0';
    }
    while(num > 0){
        int rem = num % B;
        if(rem < 10){
            temp[idx++] = '0' + rem;
        }
        else{
            temp[idx++] = 'A' + (rem -10);
        }
        num /= B;
    }
    // Reverse the string
    int i;
    for(i=0; i<idx; i++) {
        str[i] = temp[idx-1-i];
    }
    str[idx] = '\0';
}

// Function to check if a string is palindrome
int is_palindrome(char* str){
    int len = strlen(str);
    int i;
    for(i=0; i<len/2; i++){
        if(str[i] != str[len-1-i]){
            return 0;
        }
    }
    return 1;
}

int main(){
    int B;
    scanf("%d", &B);
    int n;
    char num_str[MAX_DIGITS];
    char square_str[MAX_DIGITS];
    for(n=1; n<=300; n++){
        long square = (long)n * (long)n;
        convert_to_base(n, B, num_str);
        convert_to_base(square, B, square_str);
        if(is_palindrome(square_str)){
            printf("%s %s\n", num_str, square_str);
        }
    }
    return 0;
}