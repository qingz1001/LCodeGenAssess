#include <stdio.h>
#include <string.h>

// 定义高精度数的结构体
typedef struct {
    int digit[1000]; // 存储高精度数的每一位
    int length;      // 高精度数的长度
} BigInt;

// 初始化高精度数
void initBigInt(BigInt *b) {
    memset(b->digit, 0, sizeof(b->digit));
    b->length = 1;
}

// 计算n的阶乘并存储到高精度数b中
void factorial(BigInt *b, int n) {
    BigInt result;
    initBigInt(&result);
    result.digit[0] = 1;
    result.length = 1;

    for (int i = 2; i <= n; i++) {
        BigInt temp;
        initBigInt(&temp);
        temp.digit[0] = 1;
        temp.length = 1;

        for (int j = 0; j < result.length; j++) {
            temp.digit[j] += result.digit[j] * i;
            temp.digit[j + 1] += temp.digit[j] / 10;
            temp.digit[j] %= 10;
        }

        while (temp.digit[temp.length] > 0) {
            temp.length++;
        }

        result.length = temp.length;
        for (int k = 0; k < result.length; k++) {
            result.digit[k] = temp.digit[k];
        }
    }

    b->length = result.length;
    for (int k = 0; k < b->length; k++) {
        b->digit[k] = result.digit[k];
    }
}

// 高精度数相加
void addBigInt(BigInt *a, BigInt b) {
    BigInt result;
    initBigInt(&result);

    int carry = 0;
    for (int i = 0; i < a->length || i < b.length || carry > 0; i++) {
        result.digit[i] = a->digit[i] + b.digit[i] + carry;
        carry = result.digit[i] / 10;
        result.digit[i] %= 10;
    }

    result.length = carry > 0 ? a->length + 1 : a->length;
    while (result.digit[result.length - 1] == 0 && result.length > 1) {
        result.length--;
    }

    a->length = result.length;
    for (int i = 0; i < a->length; i++) {
        a->digit[i] = result.digit[i];
    }
}

// 打印高精度数
void printBigInt(BigInt b) {
    for (int i = b.length - 1; i >= 0; i--) {
        printf("%d", b.digit[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    BigInt sum;
    initBigInt(&sum);

    for (int i = 1; i <= n; i++) {
        BigInt temp;
        factorial(&temp, i);
        addBigInt(&sum, temp);
    }

    printBigInt(sum);

    return 0;
}