#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 求两个数的最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 分数结构体
typedef struct {
    int numerator; // 分子
    int denominator; // 分母
} Fraction;

// 化简分数
void reduceFraction(Fraction *f) {
    int divisor = gcd(f->numerator, f->denominator);
    f->numerator /= divisor;
    f->denominator /= divisor;
}

// 分数相加
Fraction addFractions(Fraction f1, Fraction f2) {
    Fraction result;
    result.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    result.denominator = f1.denominator * f2.denominator;
    reduceFraction(&result);
    return result;
}

// 分数相减
Fraction subtractFractions(Fraction f1, Fraction f2) {
    Fraction result;
    result.numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    result.denominator = f1.denominator * f2.denominator;
    reduceFraction(&result);
    return result;
}

// 分数相除
Fraction divideFractions(Fraction f1, Fraction f2) {
    Fraction result;
    result.numerator = f1.numerator * f2.denominator;
    result.denominator = f1.denominator * f2.numerator;
    reduceFraction(&result);
    return result;
}

int main() {
    char input[101];
    scanf("%s", input);

    Fraction result;
    result.numerator = 0;
    result.denominator = 1;

    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == '+') {
            i++;
            Fraction f;
            f.numerator = atoi(input + i);
            while (input[i] >= '0' && input[i] <= '9') {
                i++;
            }
            f.denominator = atoi(input + i);
            while (input[i] >= '0' && input[i] <= '9') {
                i++;
            }
            result = addFractions(result, f);
        } else if (input[i] == '-') {
            i++;
            Fraction f;
            f.numerator = atoi(input + i);
            while (input[i] >= '0' && input[i] <= '9') {
                i++;
            }
            f.denominator = atoi(input + i);
            while (input[i] >= '0' && input[i] <= '9') {
                i++;
            }
            result = subtractFractions(result, f);
        } else if (input[i] == '/') {
            i++;
            Fraction f;
            f.numerator = atoi(input + i);
            while (input[i] >= '0' && input[i] <= '9') {
                i++;
            }
            f.denominator = atoi(input + i);
            while (input[i] >= '0' && input[i] <= '9') {
                i++;
            }
            result = divideFractions(result, f);
        }
    }

    if (result.denominator == 1) {
        printf("%d\n", result.numerator);
    } else {
        printf("%d/%d\n", result.numerator, result.denominator);
    }

    return 0;
}