#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define MAXM 100000

typedef struct {
    int A, B, C;
} Recipe;

int N;
int price[MAXN];
Recipe recipes[MAXM];
int recipe_count = 0;

long long min_cost[MAXN];
long long ways[MAXN];

void read_input() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &price[i]);
    }
    while (scanf("%d %d %d", &recipes[recipe_count].A, &recipes[recipe_count].B, &recipes[recipe_count].C) != EOF) {
        recipe_count++;
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        min_cost[i] = price[i];
        ways[i] = 1;
    }

    int updated = 1;
    while (updated) {
        updated = 0;
        for (int i = 0; i < recipe_count; i++) {
            int A = recipes[i].A;
            int B = recipes[i].B;
            int C = recipes[i].C;
            if (min_cost[A] + min_cost[B] < min_cost[C]) {
                min_cost[C] = min_cost[A] + min_cost[B];
                ways[C] = ways[A] * ways[B];
                updated = 1;
            } else if (min_cost[A] + min_cost[B] == min_cost[C]) {
                ways[C] += ways[A] * ways[B];
            }
        }
    }
}

void print_result() {
    printf("%lld %lld\n", min_cost[0], ways[0]);
}

int main() {
    read_input();
    solve();
    print_result();
    return 0;
}