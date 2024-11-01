#include <stdio.h>
#include <stdlib.h>

#define LL long long

typedef struct {
    LL S, K, R;
} Monster;

int compare(const void *a, const void *b) {
    return ((Monster *)b)->K - ((Monster *)a)->K;
}

int main() {
    int N;
    scanf("%d", &N);
    Monster *monsters = (Monster *)malloc(N * sizeof(Monster));
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld %lld", &monsters[i].S, &monsters[i].K, &monsters[i].R);
    }

    qsort(monsters, N, sizeof(Monster), compare);

    LL total_cost = 0;
    for (int i = 0; i < N; i++) {
        if (monsters[i].R == 0) {
            total_cost += monsters[i].K;
        } else {
            total_cost += monsters[i].S;
        }
    }

    printf("%lld\n", total_cost);

    free(monsters);
    return 0;
}