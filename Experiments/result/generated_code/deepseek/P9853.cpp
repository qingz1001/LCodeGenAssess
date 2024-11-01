#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 200000
#define MAX_Q 200000

typedef struct {
    long long a, b, c;
} Equation;

Equation equations[MAX_N];
bool solutions[MAX_N];

long long solve_equation(long long a, long long b, long long c) {
    if (a == 0) return -1; // Invalid equation
    return (c - b) / a;
}

int main() {
    int n, Q;
    scanf("%d %d", &n, &Q);

    for (int i = 0; i < n; i++) {
        char eq[50];
        scanf("%s", eq);

        long long a = 0, b = 0, c = 0;
        int sign_a = 1, sign_b = 1, sign_c = 1;
        int state = 0; // 0: reading a, 1: reading b, 2: reading c

        for (int j = 0; eq[j] != '\0'; j++) {
            if (eq[j] == 'x') {
                state = 1;
                continue;
            } else if (eq[j] == '=') {
                state = 2;
                continue;
            } else if (eq[j] == '+') {
                sign_b = 1;
                continue;
            } else if (eq[j] == '-') {
                if (state == 0) sign_a = -1;
                else if (state == 1) sign_b = -1;
                else sign_c = -1;
                continue;
            }

            if (state == 0) {
                a = a * 10 + (eq[j] - '0');
            } else if (state == 1) {
                b = b * 10 + (eq[j] - '0');
            } else {
                c = c * 10 + (eq[j] - '0');
            }
        }

        a *= sign_a;
        b *= sign_b;
        c *= sign_c;

        equations[i].a = a;
        equations[i].b = b;
        equations[i].c = c;
    }

    memset(solutions, false, sizeof(solutions));

    for (int i = 0; i < n; i++) {
        long long x = solve_equation(equations[i].a, equations[i].b, equations[i].c);
        if (x > 0) {
            solutions[x] = true;
        }
    }

    for (int q = 0; q < Q; q++) {
        long long L, R;
        scanf("%lld %lld", &L, &R);

        int count = 0;
        for (long long x = L; x <= R; x++) {
            if (solutions[x]) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}