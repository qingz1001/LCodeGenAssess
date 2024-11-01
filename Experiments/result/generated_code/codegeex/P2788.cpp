#include <stdio.h>
#include <string.h>

int main() {
    char input[60001];
    scanf("%s", input);
    
    long long result = 0;
    int i = 0;
    int sign = 1; // 1 for positive, -1 for negative
    
    while (input[i] != '\0') {
        if (input[i] == '+') {
            sign = 1;
        } else if (input[i] == '-') {
            sign = -1;
        } else {
            long long num = 0;
            while (input[i] >= '0' && input[i] <= '9') {
                num = num * 10 + (input[i] - '0');
                i++;
            }
            result += num * sign;
        }
        i++;
    }
    
    printf("%lld\n", result);
    return 0;
}