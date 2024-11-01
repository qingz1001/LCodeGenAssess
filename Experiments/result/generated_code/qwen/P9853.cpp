#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_Q 200005
#define MAX_LEN 100

typedef struct {
    int a;
    int b;
    int c;
} Equation;

Equation equations[MAX_N];
int solutions[MAX_N];

int main() {
    int n, Q;
    scanf("%d %d", &n, &Q);

    for (int i = 0; i < n; ++i) {
        char equation[MAX_LEN];
        scanf("%s", equation);
        sscanf(equation, "%dx+%d=%d", &equations[i].a, &equations[i].b, &equations[i].c);
    }

    for (int i = 0; i < n; ++i) {
        if (equations[i].a == 0) {
            if (equations[i].b == equations[i].c) {
                solutions[i] = 1;
            } else {
                solutions[i] = 0;
            }
        } else {
            solutions[i] = abs((equations[i].c - equations[i].b) / equations[i].a);
        }
    }

    while (Q--) {
        int L, R;
        scanf("%d %d", &L, &R);
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (solutions[i] >= L && solutions[i] <= R) {
                count++;
            }
        }
        printf("%d\n", count);
    }

    return 0;
}