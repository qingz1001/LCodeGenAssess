#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int num;
    int den;
} Fraction;

Fraction add(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.den + a.den * b.num;
    result.den = a.den * b.den;
    return result;
}

Fraction subtract(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.den - a.den * b.num;
    result.den = a.den * b.den;
    return result;
}

Fraction multiply(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.num;
    result.den = a.den * b.den;
    return result;
}

Fraction divide(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.den;
    result.den = a.den * b.num;
    return result;
}

void simplify(Fraction *f) {
    int gcd = __gcd(f->num, f->den);
    f->num /= gcd;
    f->den /= gcd;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int v[MAXN];
    for (int i = 1; i <= n; i++) {
        v[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        char op;
        scanf(" %c", &op);
        if (op == 'C') {
            int l, r, v_val;
            scanf("%d %d %d", &l, &r, &v_val);
            for (int j = l; j <= r; j++) {
                v[j]++;
            }
        } else if (op == 'Q') {
            int l, r;
            scanf("%d %d", &l, &r);
            Fraction total_cost = {0, 1};
            Fraction count = {0, 1};
            for (int j = l; j <= r; j++) {
                total_cost = add(total_cost, multiply((Fraction){v[j], 1}, count));
                count = add(count, (Fraction){1, 1});
            }
            simplify(&total_cost);
            printf("%d/%d\n", total_cost.num, total_cost.den);
        }
    }

    return 0;
}