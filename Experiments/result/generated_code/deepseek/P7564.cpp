#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2800
#define MAXQ 3000000

typedef struct {
    long long T, A, B, C;
} Customer;

typedef struct {
    long long P, X;
} Plan;

Customer customers[MAXN];
Plan plans[MAXQ];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long calculate_earnings(long long P, long long X, Customer *cust, int N) {
    long long earnings = 0;
    long long current_time = P;
    long long current_position = X;

    for (int i = 0; i < N; i++) {
        if (current_time <= cust[i].T) {
            long long time_to_reach = cust[i].T - current_time;
            long long position_at_T = current_position + time_to_reach * (cust[i].A < cust[i].B ? 1 : -1);

            if (position_at_T >= min(cust[i].A, cust[i].B) && position_at_T <= max(cust[i].A, cust[i].B)) {
                long long time_to_end = abs(cust[i].B - position_at_T);
                earnings += time_to_end * cust[i].C;
                current_time += time_to_end;
                current_position = cust[i].B;
            }
        }
    }

    return earnings;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld %lld %lld", &customers[i].T, &customers[i].A, &customers[i].B, &customers[i].C);
    }

    for (int i = 0; i < Q; i++) {
        scanf("%lld %lld", &plans[i].P, &plans[i].X);
    }

    for (int i = 0; i < Q; i++) {
        long long result = calculate_earnings(plans[i].P, plans[i].X, customers, N);
        printf("%lld\n", result);
    }

    return 0;
}