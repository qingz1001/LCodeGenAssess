#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2800
#define MAX_Q 3000000
#define INF 1e9

typedef struct {
    int T, A, B, C;
} Customer;

typedef struct {
    int P, X;
} Scheme;

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    Customer customers[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d %d", &customers[i].T, &customers[i].A, &customers[i].B, &customers[i].C);
    }

    Scheme schemes[MAX_Q];
    for (int j = 0; j < Q; ++j) {
        scanf("%d %d", &schemes[j].P, &schemes[j].X);
    }

    for (int j = 0; j < Q; ++j) {
        int max_salary = 0;
        for (int i = 0; i < N; ++i) {
            int start_time = schemes[j].P;
            if (start_time > customers[i].T) {
                start_time = customers[i].T;
            }
            int end_time = start_time + abs(customers[i].B - customers[i].A);
            if (end_time < schemes[j].P + abs(schemes[j].X - customers[i].A)) {
                continue;
            }
            int path_length = abs(customers[i].B - customers[i].A) + abs(schemes[j].X - customers[i].A);
            int salary = path_length * customers[i].C / 2;
            if (salary > max_salary) {
                max_salary = salary;
            }
        }
        printf("%d\n", max_salary);
    }

    return 0;
}