#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char digits[] = "0123456789ABCDEF";

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void convertToNegativeBase(int n, int r) {
    char result[100] = {0};
    int index = 0;
    int absN = abs(n);
    
    if (absN == 0) {
        printf("%d=0(base%d)\n", n, r);
        return;
    }
    
    while (absN != 0) {
        int remainder = absN % (-r);
        absN = absN / (-r);
        
        if (remainder < 0) {
            remainder += (-r);
            absN++;
        }
        
        result[index++] = digits[remainder];
    }
    
    result[index] = '\0';
    reverse(result);
    
    printf("%d=%s(base%d)\n", n, result, r);
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    convertToNegativeBase(n, r);
    return 0;
}