#include <stdio.h>
#include <stdlib.h>

// 函数用于计算最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 结构体用于存储分数
typedef struct {
    int numerator;
    int denominator;
} Fraction;

// 比较函数用于qsort
int compare(const void *a, const void *b) {
    Fraction *f1 = (Fraction *)a;
    Fraction *f2 = (Fraction *)b;
    return (f1->numerator * f2->denominator - f2->numerator * f1->denominator);
}

int main() {
    int n;
    scanf("%d", &n);

    Fraction fractions[n * n];
    int count = 0;

    // 生成所有满足条件的分数
    for (int b = 1; b <= n; b++) {
        for (int a = 0; a <= b; a++) {
            if (gcd(a, b) == 1) {
                fractions[count].numerator = a;
                fractions[count].denominator = b;
                count++;
            }
        }
    }

    // 使用qsort对分数进行排序
    qsort(fractions, count, sizeof(Fraction), compare);

    // 输出排序后的分数
    for (int i = 0; i < count; i++) {
        printf("%d/%d\n", fractions[i].numerator, fractions[i].denominator);
    }

    return 0;
}