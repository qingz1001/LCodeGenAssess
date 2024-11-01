#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int magic(int n) {
    if (n < 10) return n;
    
    char num[11];
    sprintf(num, "%d", n);
    int len = strlen(num);
    
    char result[10];
    int res_len = 0;
    
    for (int i = 1; i < len; i++) {
        int diff = abs(num[i] - num[i-1]);
        result[res_len++] = diff + '0';
    }
    
    while (res_len > 1 && result[0] == '0') {
        for (int i = 0; i < res_len - 1; i++) {
            result[i] = result[i+1];
        }
        res_len--;
    }
    
    result[res_len] = '\0';
    return atoi(result);
}

int magic_fingerprint(int n) {
    while (n >= 10) {
        n = magic(n);
    }
    return n;
}

int main() {
    int A, B;
    scanf("%d", &A);
    scanf("%d", &B);
    
    int lucky_count = 0;
    for (int i = A; i <= B; i++) {
        if (magic_fingerprint(i) == 7) {
            lucky_count++;
        }
    }
    
    printf("%d\n", lucky_count);
    
    return 0;
}