#include <stdio.h>

// 函数用于计算一个数的所有真约数之和
int sum_of_proper_divisors(int n) {
    int sum = 1; // 1 是所有数的真约数
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int main() {
    int s;
    scanf("%d", &s);

    // 从 s 开始寻找第一个“非常好友”
    for (int a = s; ; a++) {
        int b = sum_of_proper_divisors(a);
        if (b > a && sum_of_proper_divisors(b) == a) {
            printf("%d %d\n", a, b);
            break;
        }
    }

    return 0;
}