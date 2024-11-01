#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    scanf("%s", s);
    
    int a[6] = {0}, b[6] = {0};
    int i = 0, j = 0;
    while (s[i] != '+') {
        if (s[i] == ',') {
            i++;
            continue;
        }
        a[j++] = s[i++] - '0';
    }
    
    i += 2;
    j = 0;
    while (i < strlen(s)) {
        if (s[i] == ',') {
            i++;
            continue;
        }
        b[j++] = s[i++] - '0';
    }
    
    int carry = 0, result[6] = {0};
    for (int k = 5; k >= 0; k--) {
        int sum = a[k] + b[k] + carry;
        result[k] = sum % (k * 2 + 3);
        carry = sum / (k * 2 + 3);
    }
    
    for (int k = 0; k <= 5; k++) {
        printf("%d,", result[k]);
    }
    printf("\n");
    
    return 0;
}