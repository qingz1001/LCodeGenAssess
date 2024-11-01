#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXM 100000

typedef struct {
    int a, b;
    double debt;
} Report;

Report reports[MAXM];
double debts[MAXN + 1];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %lf", &reports[i].a, &reports[i].b, &reports[i].debt);
    }

    // Initialize debts to zero
    for (int i = 1; i <= N; i++) {
        debts[i] = 0.0;
    }

    // Set the debt of the first student to 0.00
    debts[1] = 0.00;

    // Calculate debts for the rest of the students
    for (int i = 0; i < M; i++) {
        int a = reports[i].a;
        int b = reports[i].b;
        double debt = reports[i].debt;

        if (debts[a] == 0.00 && debts[b] == 0.00) {
            // Both debts are unknown, set one to the debt value
            debts[a] = debt;
        } else if (debts[a] != 0.00 && debts[b] == 0.00) {
            // Debt of a is known, calculate debt of b
            debts[b] = debts[a] + debt;
        } else if (debts[a] == 0.00 && debts[b] != 0.00) {
            // Debt of b is known, calculate debt of a
            debts[a] = debts[b] - debt;
        } else {
            // Both debts are known, check consistency
            if (debts[a] + debts[b] != debt) {
                printf("IMPOSSIBLE\n");
                return 0;
            }
        }
    }

    // Output the debts
    for (int i = 1; i <= N; i++) {
        printf("%.2f\n", debts[i]);
    }

    return 0;
}