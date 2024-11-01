#include <stdio.h>
#include <string.h>

// 定义高精度数的结构体
typedef struct {
    int digits[100]; // 用于存储高精度数的每一位
    int length;      // 高精度数的长度
} BigInt;

// 初始化高精度数
void init(BigInt *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->length = 1;
}

// 计算一个数的阶乘
void factorial(BigInt *result, int n) {
    BigInt temp, one;
    init(&temp);
    init(&one);
    one.digits[0] = 1;
    one.length = 1;

    for (int i = 1; i <= n; i++) {
        BigInt product;
        init(&product);

        for (int j = 0; j < one.length; j++) {
            int carry = 0;
            for (int k = 0; k < temp.length; k++) {
                int mul = temp.digits[k] * i + carry;
                product.digits[k] = mul % 10;
                carry = mul / 10;
            }
            while (carry > 0) {
                product.digits[temp.length++] = carry % 10;
                carry /= 10;
            }
        }

        memcpy(&temp, &product, sizeof(BigInt));
    }

    *result = temp;
}

// 高精度数加法
void add(BigInt *result, BigInt a, BigInt b) {
    BigInt sum;
    init(&sum);

    int carry = 0;
    int len = a.length > b.length ? a.length : b.length;
    for (int i = 0; i < len; i++) {
        int temp = a.digits[i] + b.digits[i] + carry;
        sum.digits[i] = temp % 10;
        carry = temp / 10;
    }

    if (carry > 0) {
        sum.digits[len++] = carry;
    }

    sum.length = len;
    *result = sum;
}

int main() {
    int n;
    scanf("%d", &n);

    BigInt sum;
    init(&sum);

    for (int i = 1; i <= n; i++) {
        BigInt factorialResult;
        factorial(&factorialResult, i);
        add(&sum, sum, factorialResult);
    }

    for (int i = sum.length - 1; i >= 0; i--) {
        printf("%d", sum.digits[i]);
    }
    printf("\n");

    return 0;
}