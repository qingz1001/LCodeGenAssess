#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2800
#define MAXQ 3000000

typedef struct {
    int T, A, B, C;
} Customer;

typedef struct {
    int P, X;
} Plan;

Customer customers[MAXN];
Plan plans[MAXQ];

int compare_customers(const void *a, const void *b) {
    Customer *c1 = (Customer *)a;
    Customer *c2 = (Customer *)b;
    if (c1->T != c2->T) return c1->T - c2->T;
    return c1->A - c2->A;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &customers[i].T, &customers[i].A, &customers[i].B, &customers[i].C);
    }

    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &plans[i].P, &plans[i].X);
    }

    qsort(customers, N, sizeof(Customer), compare_customers);

    for (int i = 0; i < Q; i++) {
        int P = plans[i].P;
        int X = plans[i].X;
        double max_earnings = 0.0;

        for (int j = 0; j < N; j++) {
            int T = customers[j].T;
            int A = customers[j].A;
            int B = customers[j].B;
            int C = customers[j].C;

            if (P <= T) {
                double time_to_reach = (double)(A - X) / (T - P);
                if (time_to_reach >= 0) {
                    double distance = (double)(B - A) / (T - P);
                    double earnings = distance * C;
                    if (earnings > max_earnings) {
                        max_earnings = earnings;
                    }
                }
            }
        }

        printf("%.0f\n", max_earnings);
    }

    return 0;
}