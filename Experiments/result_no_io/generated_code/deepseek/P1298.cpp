#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int numerator;
    int denominator;
    double value;
} Fraction;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int compare(const void *a, const void *b) {
    Fraction *fracA = (Fraction *)a;
    Fraction *fracB = (Fraction *)b;
    if (fracA->value < fracB->value) return -1;
    if (fracA->value > fracB->value) return 1;
    return 0;
}

int main() {
    int M, N;
    double R;
    scanf("%d %d", &M, &N);
    scanf("%lf", &R);

    Fraction *fractions = (Fraction *)malloc((M * N) * sizeof(Fraction));
    int count = 0;

    for (int i = 0; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (gcd(i, j) == 1) {
                fractions[count].numerator = i;
                fractions[count].denominator = j;
                fractions[count].value = (double)i / j;
                count++;
            }
        }
    }

    qsort(fractions, count, sizeof(Fraction), compare);

    double minDiff = fabs(fractions[0].value - R);
    int minIndex = 0;
    int multipleSolutions = 0;

    for (int i = 1; i < count; i++) {
        double diff = fabs(fractions[i].value - R);
        if (diff < minDiff) {
            minDiff = diff;
            minIndex = i;
            multipleSolutions = 0;
        } else if (diff == minDiff) {
            multipleSolutions = 1;
        }
    }

    if (multipleSolutions) {
        printf("TOO MANY\n");
    } else {
        if (fractions[minIndex].denominator == 1) {
            printf("%d\n", fractions[minIndex].numerator);
        } else {
            printf("%d/%d\n", fractions[minIndex].numerator, fractions[minIndex].denominator);
        }
    }

    free(fractions);
    return 0;
}