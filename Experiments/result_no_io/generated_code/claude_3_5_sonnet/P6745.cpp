#include <stdio.h>
#include <string.h>

void multiply_by_10(char *num) {
    int len = strlen(num);
    int carry = 0;
    
    for (int i = len - 1; i >= 0; i--) {
        int digit = (num[i] - '0') * 10 + carry;
        num[i] = (digit % 10) + '0';
        carry = digit / 10;
    }
    
    if (carry > 0) {
        memmove(num + 1, num, len + 1);
        num[0] = carry + '0';
    }
}

void add_numbers(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int carry = 0;
    
    for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry; i--, j--) {
        int sum = carry;
        if (i >= 0) sum += num1[i] - '0';
        if (j >= 0) sum += num2[j] - '0';
        
        num1[i < 0 ? 0 : i] = (sum % 10) + '0';
        carry = sum / 10;
        
        if (i < 0 && (j >= 0 || carry)) {
            memmove(num1 + 1, num1, len1 + 1);
            len1++;
        }
    }
}

int main() {
    int k;
    char x[20];
    char result[502] = "1";
    
    scanf("%d %s", &k, x);
    
    for (int i = 0; i < k; i++) {
        multiply_by_10(result);
    }
    
    add_numbers(result, x);
    
    printf("%s\n", result);
    
    return 0;
}