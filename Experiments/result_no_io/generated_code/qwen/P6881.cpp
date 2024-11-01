#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXQ 200005

int N, Q;
long long S[MAXN];
int T[MAXQ], L[MAXQ], R[MAXQ];

void update(int i, int val) {
    for (; i <= N; i += i & -i) {
        S[i] = val;
    }
}

long long query(int i) {
    long long res = 0;
    for (; i > 0; i -= i & -i) {
        res = S[i];
    }
    return res;
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &S[i]);
    }
    for (int j = 0; j < Q; ++j) {
        scanf("%d %d %d", &T[j], &L[j], &R[j]);
    }

    long long total_cost = 0;
    for (int j = Q - 1; j >= 0; --j) {
        total_cost += query(R[j]) * (R[j] - L[j] + 1);
        update(L[j], 0);
    }

    printf("%lld\n", total_cost);

    return 0;
}