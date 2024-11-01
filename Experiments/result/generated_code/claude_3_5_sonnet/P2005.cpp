#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 20000

char N[MAX_LEN], M[MAX_LEN];
int result[MAX_LEN];

void subtract(char *a, char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    int borrow = 0;
    
    for (int i = 0; i < len_b || borrow; i++) {
        int digit_a = (i < len_a) ? a[len_a - 1 - i] - '0' : 0;
        int digit_b = (i < len_b) ? b[len_b - 1 - i] - '0' : 0;
        
        digit_a -= borrow;
        if (digit_a < digit_b) {
            digit_a += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        a[len_a - 1 - i] = (digit_a - digit_b) + '0';
    }
    
    while (len_a > 1 && a[0] == '0') {
        memmove(a, a + 1, len_a);
        len_a--;
    }
}

int compare(char *a, char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    if (len_a != len_b) return len_a - len_b;
    return strcmp(a, b);
}

void divide() {
    int len_n = strlen(N), len_m = strlen(M);
    int result_len = 0;
    char temp[MAX_LEN];
    
    for (int i = 0; i < len_n; i++) {
        memmove(temp + 1, temp, strlen(temp) + 1);
        temp[0] = N[i];
        
        int count = 0;
        while (compare(temp, M) >= 0) {
            subtract(temp, M);
            count++;
        }
        
        result[result_len++] = count;
    }
    
    while (result_len > 1 && result[0] == 0) {
        memmove(result, result + 1, --result_len * sizeof(int));
    }
}

int main() {
    scanf("%s", N);
    scanf("%s", M);
    
    divide();
    
    for (int i = 0; i < strlen(N); i++) {
        printf("%d", result[i]);
    }
    printf("\n");
    
    return 0;
}