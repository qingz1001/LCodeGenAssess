#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 10001

void subtract(char *a, char *b) {
    int carry = 0;
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    for (int i = 0; i < len_b || carry; i++) {
        int digit_a = (i < len_a) ? a[len_a - 1 - i] - '0' : 0;
        int digit_b = (i < len_b) ? b[len_b - 1 - i] - '0' : 0;
        int result = digit_a - digit_b - carry;
        
        if (result < 0) {
            result += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        
        if (i < len_a) {
            a[len_a - 1 - i] = result + '0';
        }
    }
    
    while (len_a > 1 && a[0] == '0') {
        memmove(a, a + 1, len_a);
        len_a--;
    }
}

int compare(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    if (len_a != len_b) {
        return len_a - len_b;
    }
    
    return strcmp(a, b);
}

void multiply(char *a, int n) {
    int carry = 0;
    int len = strlen(a);
    
    for (int i = len - 1; i >= 0; i--) {
        int digit = (a[i] - '0') * n + carry;
        a[i] = (digit % 10) + '0';
        carry = digit / 10;
    }
    
    if (carry > 0) {
        memmove(a + 1, a, len + 1);
        a[0] = carry + '0';
    }
}

int main() {
    char m[MAX_DIGITS];
    int n;
    
    scanf("%s %d", m, &n);
    
    int count = 0;
    char power[MAX_DIGITS] = "1";
    
    while (compare(m, "0") > 0) {
        if (compare(m, power) >= 0) {
            subtract(m, power);
            count++;
        } else {
            multiply(power, n);
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}