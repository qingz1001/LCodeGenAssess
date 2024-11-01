#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPTH 100
#define MAX_RESULT 100

typedef struct {
    int numerator;
    int denominator;
} Fraction;

Fraction best_result[MAX_RESULT];
int best_result_size = 0;
Fraction current_result[MAX_RESULT];
int current_result_size = 0;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void simplify(Fraction *f) {
    int g = gcd(f->numerator, f->denominator);
    f->numerator /= g;
    f->denominator /= g;
}

int compare_fractions(Fraction a, Fraction b) {
    return (long long)a.numerator * b.denominator - (long long)b.numerator * a.denominator;
}

void update_best_result() {
    if (best_result_size == 0 || current_result_size < best_result_size ||
        (current_result_size == best_result_size &&
         compare_fractions(current_result[current_result_size - 1], best_result[best_result_size - 1]) > 0)) {
        memcpy(best_result, current_result, sizeof(Fraction) * current_result_size);
        best_result_size = current_result_size;
    }
}

void search(Fraction target, int min_denominator, int depth) {
    if (depth >= MAX_DEPTH) return;
    
    if (target.numerator == 1) {
        current_result[current_result_size++] = target;
        update_best_result();
        current_result_size--;
        return;
    }
    
    int start = (target.denominator + target.numerator - 1) / target.numerator;
    if (start < min_denominator) start = min_denominator;
    
    for (int i = start; i <= 10000000; i++) {
        Fraction unit = {1, i};
        if (compare_fractions(target, unit) < 0) break;
        
        Fraction next_target = {target.numerator * i - target.denominator, target.denominator * i};
        simplify(&next_target);
        
        if (next_target.denominator > 10000000) continue;
        
        current_result[current_result_size++] = unit;
        search(next_target, i + 1, depth + 1);
        current_result_size--;
    }
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    Fraction target = {a, b};
    simplify(&target);
    
    search(target, 2, 0);
    
    for (int i = 0; i < best_result_size; i++) {
        printf("%d", best_result[i].denominator);
        if (i < best_result_size - 1) printf(" ");
    }
    printf("\n");
    
    return 0;
}