#include <stdio.h>
#include <string.h>

int main() {
    char s[60010];
    long long sum = 0, num = 0, sign = 1;
    scanf("%s", s);
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            num = num * 10 + s[i] - '0';
        } else {
            sum += sign * num;
            num = 0;
            if (s[i] == '+') {
                sign = 1;
            } else if (s[i] == '-') {
                sign = -1;
            }
        }
    }
    sum += sign * num;
    printf("%lld\n", sum);
    return 0;
}