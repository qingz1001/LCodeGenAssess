#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200001

typedef struct Equation {
    int a;
    int b;
    int c;
} Equation;

int main() {
    int n, Q;
    scanf("%d %d", &n, &Q);

    Equation equations[MAX_N];
    for (int i = 0; i < n; i++) {
        char equation[20];
        scanf("%s", equation);
        equations[i].a = atoi(equation);
        equations[i].b = atoi(equation + 2);
        equations[i].c = atoi(equation + 4);
    }

    for (int i = 0; i < n; i++) {
        if (equations[i].a < 0) {
            equations[i].a = -equations[i].a;
            equations[i].b = -equations[i].b;
            equations[i].c = -equations[i].c;
        }
        equations[i].c -= equations[i].b;
        equations[i].b = 0;
    }

    for (int i = 0; i < n; i++) {
        int x = equations[i].c / equations[i].a;
        if (equations[i].c % equations[i].a == 0) {
            equations[i].c = x;
        } else {
            equations[i].c = x + 1;
        }
    }

    for (int i = 1; i < n; i++) {
        equations[i].c = equations[i].c < equations[i - 1].c ? equations[i].c : equations[i - 1].c;
    }

    for (int i = 0; i < Q; i++) {
        int L, R;
        scanf("%d %d", &L, &R);
        int ans = 0;
        for (int j = 0; j < n; j++) {
            if (equations[j].c >= L) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}