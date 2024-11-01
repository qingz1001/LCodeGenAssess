#include <stdio.h>

// 计算一个数的各位数字之和
int digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// 判断一个数是否是Rabbit Number
int isRabbitNumber(int x) {
    int sx = digitSum(x);
    int sx2 = digitSum(x * x);
    return sx2 == sx * sx;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);

    int count = 0;
    for (int i = L; i <= R; i++) {
        if (isRabbitNumber(i)) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}