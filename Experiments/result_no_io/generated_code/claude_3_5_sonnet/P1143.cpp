#include <stdio.h>
#include <string.h>
#include <math.h>

long long convert_to_decimal(char *num, int base) {
    long long result = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        int digit;
        if (num[i] >= '0' && num[i] <= '9') {
            digit = num[i] - '0';
        } else {
            digit = num[i] - 'A' + 10;
        }
        result += digit * pow(base, len - i - 1);
    }
    return result;
}

void convert_from_decimal(long long num, int base) {
    char result[100];
    int index = 0;
    
    while (num > 0) {
        int remainder = num % base;
        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
        num /= base;
    }
    
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");
}

int main() {
    int n, m;
    char num[100];
    
    scanf("%d", &n);
    scanf("%s", num);
    scanf("%d", &m);
    
    long long decimal = convert_to_decimal(num, n);
    convert_from_decimal(decimal, m);
    
    return 0;
}