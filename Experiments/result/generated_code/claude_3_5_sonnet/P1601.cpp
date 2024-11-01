#include <stdio.h>
#include <string.h>

#define MAX_LEN 501

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void add(char *a, char *b, char *result) {
    reverse(a);
    reverse(b);
    
    int carry = 0;
    int i = 0, j = 0, k = 0;
    
    while (i < strlen(a) || j < strlen(b) || carry) {
        int sum = carry;
        if (i < strlen(a)) sum += a[i] - '0';
        if (j < strlen(b)) sum += b[j] - '0';
        
        result[k] = (sum % 10) + '0';
        carry = sum / 10;
        
        i++;
        j++;
        k++;
    }
    
    result[k] = '\0';
    reverse(result);
}

int main() {
    char a[MAX_LEN], b[MAX_LEN], result[MAX_LEN + 1];
    
    scanf("%s", a);
    scanf("%s", b);
    
    add(a, b, result);
    
    printf("%s\n", result);
    
    return 0;
}