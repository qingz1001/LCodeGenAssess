#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000

typedef struct {
    int A, B, C;
} Recipe;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);

    int price[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d", &price[i]);
    }

    Recipe recipes[MAXN];
    int recipeCount = 0;
    while (1) {
        int A, B, C;
        if (scanf("%d %d %d", &A, &B, &C) != 3) break;
        recipes[recipeCount].A = A;
        recipes[recipeCount].B = B;
        recipes[recipeCount].C = C;
        recipeCount++;
    }

    int cost[MAXN];
    long long ways[MAXN];
    for (int i = 0; i < N; i++) {
        cost[i] = price[i];
        ways[i] = 1;
    }

    int updated = 1;
    while (updated) {
        updated = 0;
        for (int i = 0; i < recipeCount; i++) {
            int A = recipes[i].A;
            int B = recipes[i].B;
            int C = recipes[i].C;
            if (cost[A] + cost[B] < cost[C]) {
                cost[C] = cost[A] + cost[B];
                ways[C] = ways[A] * ways[B];
                updated = 1;
            } else if (cost[A] + cost[B] == cost[C]) {
                ways[C] += ways[A] * ways[B];
            }
        }
    }

    printf("%d %lld\n", cost[0], ways[0]);

    return 0;
}