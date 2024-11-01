#include <stdio.h>
#include <string.h>

#define MAX 505

int main(){
    char a[MAX], b[MAX];
    char result[MAX + 1];
    int len_a, len_b, len, carry = 0, sum;
    scanf("%s %s", a, b);
    len_a = strlen(a);
    len_b = strlen(b);
    len = len_a > len_b ? len_a : len_b;
    result[len] = '\0';
    for(int i = 0; i < len; i++){
        int digit_a = len_a - 1 - i >= 0 ? a[len_a - 1 - i] - '0' : 0;
        int digit_b = len_b - 1 - i >= 0 ? b[len_b - 1 - i] - '0' : 0;
        sum = digit_a + digit_b + carry;
        carry = sum / 10;
        result[len - 1 - i] = (sum % 10) + '0';
    }
    if(carry){
        printf("%d%s\n", carry, result);
    }
    else{
        printf("%s\n", result);
    }
    return 0;
}