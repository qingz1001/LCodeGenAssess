#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
    double value;
} Fraction;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int compare(const void *a, const void *b) {
    Fraction *fa = (Fraction *)a;
    Fraction *fb = (Fraction *)b;
    if (fa->value < fb->value) return -1;
    if (fa->value > fb->value) return 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    Fraction fractions[25600];  // 足够大的数组来存储所有可能的分数
    int count = 0;

    for (int denominator = 1; denominator <= n; denominator++) {
        for (int numerator = 0; numerator <= denominator; numerator++) {
            if (gcd(numerator, denominator) == 1) {
                fractions[count].numerator = numerator;
                fractions[count].denominator = denominator;
                fractions[count].value = (double)numerator / denominator;
                count++;
            }
        }
    }

    qsort(fractions, count, sizeof(Fraction), compare);

    for (int i = 0; i < count; i++) {
        printf("%d/%d\n", fractions[i].numerator, fractions[i].denominator);
    }

    return 0;
}