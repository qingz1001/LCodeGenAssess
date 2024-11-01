#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 32

long long convert_to_decimal(char* num, int base) {
    long long result = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        result = result * base + (num[i] - '0');
    }
    return result;
}

char* convert_to_base(long long num, int base) {
    static char result[MAX_LEN];
    int index = 0;
    
    while (num > 0) {
        result[index++] = num % base + '0';
        num /= base;
    }
    result[index] = '\0';
    
    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - 1 - i];
        result[index - 1 - i] = temp;
    }
    
    return result;
}

int main() {
    char binary[MAX_LEN], ternary[MAX_LEN];
    scanf("%s", binary);
    scanf("%s", ternary);
    
    int binary_len = strlen(binary);
    int ternary_len = strlen(ternary);
    
    for (long long i = 0; i <= 1000000000; i++) {
        char* bin = convert_to_base(i, 2);
        char* ter = convert_to_base(i, 3);
        
        int bin_diff = 0, ter_diff = 0;
        
        if (strlen(bin) == binary_len && strlen(ter) == ternary_len) {
            for (int j = 0; j < binary_len; j++) {
                if (bin[j] != binary[j]) bin_diff++;
            }
            for (int j = 0; j < ternary_len; j++) {
                if (ter[j] != ternary[j]) ter_diff++;
            }
            
            if (bin_diff == 1 && ter_diff == 1) {
                printf("%lld\n", i);
                return 0;
            }
        }
    }
    
    return 0;
}