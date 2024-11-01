#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long S;
    long long K;
    int R;
} Monster;

int compare(const void *a, const void *b) {
    Monster *m1 = (Monster *)a;
    Monster *m2 = (Monster *)b;
    if (m1->K != m2->K) return m1->K - m2->K;
    return m2->S - m1->S;
}

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    Monster *monsters = (Monster *)malloc(N * sizeof(Monster));
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld %d", &monsters[i].S, &monsters[i].K, &monsters[i].R);
    }

    qsort(monsters, N, sizeof(Monster), compare);

    long long total_cost = 0;
    for (int i = 0; i < N; i++) {
        total_cost += monsters[i].S;
        for (int j = 0; j < monsters[i].R; j++) {
            total_cost += monsters[i].K;
        }
    }

    printf("%lld\n", total_cost);

    free(monsters);
    return 0;
}