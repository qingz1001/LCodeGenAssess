#include <stdio.h>
#include <stdbool.h>

// 函数：判断一个数是否是循环数
bool isRunaroundNumber(unsigned long long num) {
    int digits[10] = {0}; // 用于记录数字中出现的每一位
    int count = 0; // 记录已经访问的数字位数
    int start = num; // 记录循环的起点

    while (digits[num % 10] == 0) {
        digits[num % 10] = 1; // 标记当前位已访问
        num /= 10;
        count++;
    }

    if (num == 0) {
        return false; // 包含0的数不是循环数
    }

    while (count < 10) {
        int step = num % 10; // 计算需要跳过的步数
        for (int i = 0; i < step; i++) {
            num /= 10;
            if (num == 0) {
                return false; // 超出范围，不是循环数
            }
        }

        if (digits[num % 10] == 1) {
            return false; // 有重复数字，不是循环数
        }

        digits[num % 10] = 1; // 标记当前位已访问
        count++;
    }

    return num == start; // 检查是否回到起点
}

// 函数：找到第一个比给定数字大的循环数
unsigned long long findNextRunaroundNumber(unsigned long long num) {
    unsigned long long nextNum = num + 1;
    while (!isRunaroundNumber(nextNum)) {
        nextNum++;
    }
    return nextNum;
}

int main() {
    unsigned long long num;
    scanf("%llu", &num);
    unsigned long long result = findNextRunaroundNumber(num);
    printf("%llu\n", result);
    return 0;
}