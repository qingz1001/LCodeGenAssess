#include <stdio.h>
#include <string.h>

// 计算一个数的位数
int countDigits(long long num) {
    if (num == 0) return 1;
    int count = 0;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

// 判断一个数是否为杠杆数
int isLeverNumber(long long num) {
    int digits = countDigits(num);
    int leftSum = 0, rightSum = 0;
    for (int i = 0; i < digits; i++) {
        int digit = (num / (long long)pow(10, i)) % 10;
        leftSum += digit * (digits - i);
        rightSum += digit * i;
    }
    return leftSum == rightSum;
}

int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);
    int count = 0;
    for (long long i = x; i <= y; i++) {
        if (isLeverNumber(i)) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}