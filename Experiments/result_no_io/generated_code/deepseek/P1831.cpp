#include <stdio.h>
#include <string.h>

int isLeverNumber(long long num) {
    char str[20];
    sprintf(str, "%lld", num);
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        long long leftSum = 0, rightSum = 0;
        for (int j = 0; j < i; j++) {
            leftSum += (str[j] - '0') * (i - j);
        }
        for (int j = i + 1; j < len; j++) {
            rightSum += (str[j] - '0') * (j - i);
        }
        if (leftSum == rightSum) {
            return 1;
        }
    }
    return 0;
}

int countLeverNumbers(long long x, long long y) {
    int count = 0;
    for (long long num = x; num <= y; num++) {
        if (isLeverNumber(num)) {
            count++;
        }
    }
    return count;
}

int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);
    printf("%d\n", countLeverNumbers(x, y));
    return 0;
}