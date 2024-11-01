#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPTH 100
#define MAX_DENOM 10000000

typedef struct {
    int numerator;
    int denominator;
} Fraction;

Fraction best_solution[MAX_DEPTH];
int best_depth = MAX_DEPTH;

void find_egyptian_fraction(Fraction f, Fraction* solution, int depth) {
    if (f.numerator == 0) {
        if (depth < best_depth) {
            best_depth = depth;
            memcpy(best_solution, solution, depth * sizeof(Fraction));
        }
        return;
    }

    if (depth >= best_depth) return;

    int start = (f.denominator + f.numerator - 1) / f.numerator;
    for (int i = start; i <= MAX_DENOM; i++) {
        Fraction unit = {1, i};
        Fraction remainder = {f.numerator * i - f.denominator, f.denominator * i};

        if (remainder.numerator < 0) continue;

        int g = remainder.numerator;
        if (g != 0) {
            while (remainder.denominator % g != 0) {
                int temp = remainder.denominator % g;
                remainder.denominator = g;
                g = temp;
            }
            remainder.numerator /= g;
            remainder.denominator /= g;
        }

        solution[depth] = unit;
        find_egyptian_fraction(remainder, solution, depth + 1);
    }
}

int compare_fractions(const void* a, const void* b) {
    Fraction* fa = (Fraction*)a;
    Fraction* fb = (Fraction*)b;
    return fa->denominator - fb->denominator;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    Fraction f = {a, b};
    Fraction solution[MAX_DEPTH];

    find_egyptian_fraction(f, solution, 0);

    qsort(best_solution, best_depth, sizeof(Fraction), compare_fractions);

    for (int i = 0; i < best_depth; i++) {
        printf("%d", best_solution[i].denominator);
        if (i < best_depth - 1) printf(" ");
    }
    printf("\n");

    return 0;
}