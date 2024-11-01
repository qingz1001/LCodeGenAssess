#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 100000

typedef struct {
    int student;
    int amount;
} Debt;

int compare(const void *a, const void *b) {
    return ((Debt *)a)->student - ((Debt *)b)->student;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Debt debts[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &debts[i].student, &debts[i + 1].student, &debts[i].amount);
        i++;
    }

    qsort(debts, M / 2, sizeof(Debt), compare);

    double balance[MAX_N] = {0};
    for (int i = 0; i < M; i += 2) {
        if (debts[i].student == debts[i + 1].student) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
        balance[debts[i].student - 1] -= debts[i].amount;
        balance[debts[i + 1].student - 1] += debts[i].amount;
    }

    for (int i = 0; i < N; i++) {
        printf("%.2f\n", balance[i]);
    }

    return 0;
}