#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5000

// 定义一个结构体用于存储高精度数
typedef struct {
    int digits[MAX_SIZE];
    int length;
} BigInt;

// 初始化高精度数
void initBigInt(BigInt *num) {
    num->length = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        num->digits[i] = 0;
    }
}

// 高精度数乘以2
void multiplyByTwo(BigInt *num) {
    int carry = 0;
    for (int i = 0; i < num->length; i++) {
        int product = num->digits[i] * 2 + carry;
        num->digits[i] = product % 10;
        carry = product / 10;
    }
    if (carry > 0) {
        num->digits[num->length] = carry;
        num->length++;
    }
}

// 计算高精度数的位数
int calculateLength(BigInt *num) {
    return num->length;
}

// 打印高精度数
void printBigInt(BigInt *num) {
    for (int i = num->length - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

int main() {
    int P;
    scanf("%d", &P);

    BigInt result;
    initBigInt(&result);
    result.digits[0] = 1;
    result.length = 1;

    for (int i = 0; i < P; i++) {
        multiplyByTwo(&result);
    }

    result.digits[0]--;
    while (result.digits[result.length - 1] == 0 && result.length > 1) {
        result.length--;
    }

    int length = calculateLength(&result);
    printf("%d\n", length);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 50; j++) {
            if (i * 50 + j < length) {
                printf("%d", result.digits[i * 50 + j]);
            } else {
                printf("0");
            }
        }
        printf("\n");
    }

    return 0;
}