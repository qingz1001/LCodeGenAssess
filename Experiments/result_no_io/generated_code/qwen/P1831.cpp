#include <stdio.h>
#include <string.h>

int is_lever_number(long long num) {
    char str[60];
    sprintf(str, "%lld", num);
    int len = strlen(str);
    for (int i = 1; i < len - 1; i++) {
        long long left_sum = 0;
        long long right_sum = 0;
        for (int j = 0; j < i; j++) {
            left_sum += (str[j] - '0') * (i - j);
        }
        for (int j = i + 1; j < len; j++) {
            right_sum += (str[j] - '0') * (j - i);
        }
        if (left_sum == right_sum) {
            return 1;
        }
    }
    return 0;
}

int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);
    int count = 0;
    for (long long i = x; i <= y; i++) {
        if (is_lever_number(i)) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}