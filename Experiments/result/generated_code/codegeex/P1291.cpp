#include <stdio.h>
#include <stdlib.h>

// 定义最大球星名字数
#define MAX_N 33

// 定义分数结构体
typedef struct {
    long long numerator; // 分子
    long long denominator; // 分母
} Fraction;

// 函数声明
Fraction add(Fraction a, Fraction b);
Fraction multiply(Fraction a, Fraction b);
void simplify(Fraction *f);
void printFraction(Fraction f);

int main() {
    int n;
    scanf("%d", &n);

    // 初始化分数
    Fraction result = {0, 1};

    // 计算公式：n/(1-1/n)
    for (int i = 1; i <= n; i++) {
        Fraction temp = {i, 1};
        result = add(result, temp);
    }

    // 约分
    simplify(&result);

    // 输出结果
    printFraction(result);

    return 0;
}

// 分数相加
Fraction add(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return result;
}

// 分数相乘
Fraction multiply(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    return result;
}

// 约分
void simplify(Fraction *f) {
    long long gcd = 2;
    while (gcd <= f->denominator) {
        if (f->numerator % gcd == 0 && f->denominator % gcd == 0) {
            f->numerator /= gcd;
            f->denominator /= gcd;
        } else {
            gcd++;
        }
    }
}

// 打印分数
void printFraction(Fraction f) {
    // 分数是整数
    if (f.numerator % f.denominator == 0) {
        printf("%lld\n", f.numerator / f.denominator);
    } else {
        // 分数是真分数
        printf("%lld\n", f.numerator / f.denominator);
        printf("%*s%lld\n", f.numerator / f.denominator, "", f.numerator % f.denominator);
        printf("%*s-\n", f.numerator / f.denominator, "");
        printf("%*s%lld\n", f.numerator / f.denominator, "", f.denominator);
    }
}