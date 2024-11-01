#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXM 100000

int N, M;
int A[MAXM], B[MAXM];
double C[MAXM];
double debt[MAXN + 1];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %lf", &A[i], &B[i], &C[i]);
    }

    // Initialize debt array
    for (int i = 1; i <= N; i++) {
        debt[i] = 0.0;
    }

    // Set the debt of student 1 to 0 as a reference
    debt[1] = 0.0;

    // Use the first M-1 reports to calculate debts
    for (int i = 0; i < M; i++) {
        if (debt[A[i]] == 0.0 && debt[B[i]] == 0.0) {
            continue;
        }
        if (debt[A[i]] != 0.0) {
            debt[B[i]] = debt[A[i]] + C[i];
        } else {
            debt[A[i]] = debt[B[i]] - C[i];
        }
    }

    // Verify the last report
    for (int i = 0; i < M; i++) {
        if (debt[A[i]] + debt[B[i]] != C[i]) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }

    // Output the debt list
    for (int i = 1; i <= N; i++) {
        printf("%.2f\n", debt[i]);
    }

    return 0;
}