#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 500
#define MAX_STEPS 30

typedef struct {
    int digits[MAX_LEN];
    int len;
} Number;

// Convert character to digit
int char_to_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    else return toupper(c) - 'A' + 10;
}

// Convert digit to character
char digit_to_char(int d) {
    if (d >= 0 && d <= 9) return '0' + d;
    else return 'A' + (d - 10);
}

// Initialize Number from string
void init_number(Number *num, char *str, int base) {
    num->len = strlen(str);
    for(int i = 0; i < num->len; i++) {
        num->digits[i] = char_to_digit(str[num->len - 1 - i]);
    }
}

// Check if number is palindrome
int is_palindrome(Number *num) {
    for(int i = 0; i < num->len / 2; i++) {
        if(num->digits[i] != num->digits[num->len - 1 - i])
            return 0;
    }
    return 1;
}

// Reverse a number
Number reverse_number(Number *num) {
    Number rev;
    rev.len = num->len;
    for(int i = 0; i < num->len; i++) {
        rev.digits[i] = num->digits[num->len - 1 - i];
    }
    return rev;
}

// Add two numbers in base N
Number add_numbers(Number *a, Number *b, int base) {
    Number sum;
    int carry = 0, i;
    sum.len = a->len > b->len ? a->len : b->len;
    for(i = 0; i < sum.len; i++) {
        int digit_a = i < a->len ? a->digits[i] : 0;
        int digit_b = i < b->len ? b->digits[i] : 0;
        sum.digits[i] = digit_a + digit_b + carry;
        if(sum.digits[i] >= base) {
            sum.digits[i] -= base;
            carry = 1;
        }
        else carry = 0;
    }
    if(carry) {
        sum.digits[sum.len++] = carry;
    }
    return sum;
}

int main(){
    int N;
    char M_str[105];
    scanf("%d", &N);
    scanf("%s", M_str);
    
    Number current;
    init_number(&current, M_str, N);
    
    if(is_palindrome(&current)){
        printf("STEP=0");
        return 0;
    }
    
    int step;
    for(step = 1; step <= MAX_STEPS; step++){
        Number rev = reverse_number(&current);
        Number sum = add_numbers(&current, &rev, N);
        current = sum;
        if(is_palindrome(&current)){
            printf("STEP=%d", step);
            return 0;
        }
    }
    printf("Impossible!");
    return 0;
}