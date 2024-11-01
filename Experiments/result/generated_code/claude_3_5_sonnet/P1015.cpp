#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 100

char reverse[MAX_DIGITS + 1];
char sum[MAX_DIGITS + 1];
char num[MAX_DIGITS + 1];

int base;

int is_palindrome(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - 1 - i]) return 0;
    }
    return 1;
}

void reverse_string(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        reverse[i] = s[len - 1 - i];
    }
    reverse[len] = '\0';
}

int char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

char int_to_char(int n) {
    if (n < 10) return n + '0';
    return n - 10 + 'A';
}

void add_strings(char *a, char *b) {
    int carry = 0;
    int len_a = strlen(a);
    int len_b = strlen(b);
    int len = (len_a > len_b) ? len_a : len_b;
    
    for (int i = 0; i < len; i++) {
        int sum_digit = carry;
        if (i < len_a) sum_digit += char_to_int(a[len_a - 1 - i]);
        if (i < len_b) sum_digit += char_to_int(b[len_b - 1 - i]);
        
        sum[len - 1 - i] = int_to_char(sum_digit % base);
        carry = sum_digit / base;
    }
    
    if (carry > 0) {
        memmove(sum + 1, sum, len);
        sum[0] = int_to_char(carry);
        len++;
    }
    
    sum[len] = '\0';
}

int main() {
    scanf("%d", &base);
    scanf("%s", num);
    
    for (int step = 1; step <= 30; step++) {
        reverse_string(num);
        add_strings(num, reverse);
        strcpy(num, sum);
        
        if (is_palindrome(num)) {
            printf("STEP=%d\n", step);
            return 0;
        }
    }
    
    printf("Impossible!\n");
    return 0;
}