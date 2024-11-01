#include <stdio.h>
#include <string.h>

void convert_to_base(int num, int base, char *str) {
    char temp[50];
    int index = 0;
    if (num == 0) {
        temp[index++] = '0';
    }
    while (num > 0) {
        int rem = num % base;
        if (rem < 10) {
            temp[index++] = '0' + rem;
        } else {
            temp[index++] = 'A' + (rem - 10);
        }
        num /= base;
    }
    // Reverse the characters to get the correct order
    for (int i = 0; i < index; i++) {
        str[i] = temp[index - i - 1];
    }
    str[index] = '\0';
}

int is_palindrome(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len / 2; i++) {
        if(str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int main(){
    int B;
    scanf("%d", &B);
    char num_str[50], square_str[50];
    for(int n = 1; n <= 300; n++) {
        int square = n * n;
        convert_to_base(n, B, num_str);
        convert_to_base(square, B, square_str);
        if(is_palindrome(square_str)){
            printf("%s %s\n", num_str, square_str);
        }
    }
    return 0;
}