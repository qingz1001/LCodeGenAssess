#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    char s[205];
    s[0] = '1';
    s[1] = '\0';

    for (int i = 0; i < n; i++) {
        int carry = 0;
        for (int j = 0; j < strlen(s); j++) {
            int sum = (s[j] - '0') * 2 + carry;
            s[j] = sum % 10 + '0';
            carry = sum / 10;
        }
        if (carry > 0) {
            s[strlen(s)] = carry + '0';
        }
    }

    printf("%s\n", s);
    return 0;
}