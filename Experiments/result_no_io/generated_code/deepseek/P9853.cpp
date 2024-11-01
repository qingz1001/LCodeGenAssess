#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200000
#define MAX_Q 200000

typedef struct {
    long long a, b, c;
} Equation;

Equation equations[MAX_N];
int solutions[MAX_N];

long long solve_equation(long long a, long long b, long long c) {
    if (a == 0) {
        return -1; // No solution if a == 0
    }
    if ((c - b) % a != 0) {
        return -1; // No integer solution
    }
    long long x = (c - b) / a;
    return x > 0 ? x : -1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, Q;
    scanf("%d %d", &n, &Q);

    for (int i = 0; i < n; i++) {
        char eq[50];
        scanf("%s", eq);

        long long a = 0, b = 0, c = 0;
        int sign_a = 1, sign_b = 1, sign_c = 1;
        int pos = 0;

        if (eq[pos] == '-') {
            sign_a = -1;
            pos++;
        }
        while (eq[pos] >= '0' && eq[pos] <= '9') {
            a = a * 10 + (eq[pos] - '0');
            pos++;
        }
        a *= sign_a;

        pos++; // skip 'x'
        pos++; // skip '+' or '-'

        if (eq[pos] == '-') {
            sign_b = -1;
            pos++;
        }
        while (eq[pos] >= '0' && eq[pos] <= '9') {
            b = b * 10 + (eq[pos] - '0');
            pos++;
        }
        b *= sign_b;

        pos++; // skip '='

        if (eq[pos] == '-') {
            sign_c = -1;
            pos++;
        }
        while (eq[pos] >= '0' && eq[pos] <= '9') {
            c = c * 10 + (eq[pos] - '0');
            pos++;
        }
        c *= sign_c;

        equations[i].a = a;
        equations[i].b = b;
        equations[i].c = c;
    }

    int solution_count = 0;
    for (int i = 0; i < n; i++) {
        long long x = solve_equation(equations[i].a, equations[i].b, equations[i].c);
        if (x != -1) {
            solutions[solution_count++] = x;
        }
    }

    qsort(solutions, solution_count, sizeof(int), compare);

    for (int q = 0; q < Q; q++) {
        long long L, R;
        scanf("%lld %lld", &L, &R);

        int count = 0;
        for (int i = 0; i < solution_count; i++) {
            if (solutions[i] >= L && solutions[i] <= R) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}