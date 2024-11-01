#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 2147483648ULL
#define MAXW 100005
#define MAXK 10

typedef unsigned long long ull;

int N, M, W, k;
int trees[MAXW][2];
int row_count[MAXW], col_count[MAXW];
ull comb[MAXW][MAXK];

ull mod_add(ull a, ull b) {
    return (a + b) % MOD;
}

ull mod_sub(ull a, ull b) {
    return (a - b + MOD) % MOD;
}

ull mod_mul(ull a, ull b) {
    return (a * b) % MOD;
}

void precompute_combinations(int n, int k) {
    for (int i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= k && j <= i; j++) {
            comb[i][j] = mod_add(comb[i-1][j-1], comb[i-1][j]);
        }
    }
}

int compare(const void *a, const void *b) {
    int *p1 = (int *)a;
    int *p2 = (int *)b;
    if (p1[1] == p2[1]) return p1[0] - p2[0];
    return p1[1] - p2[1];
}

int main() {
    scanf("%d %d", &N, &M);
    scanf("%d", &W);
    for (int i = 0; i < W; i++) {
        scanf("%d %d", &trees[i][0], &trees[i][1]);
    }
    scanf("%d", &k);

    qsort(trees, W, sizeof(trees[0]), compare);

    memset(row_count, 0, sizeof(row_count));
    memset(col_count, 0, sizeof(col_count));

    for (int i = 0; i < W; i++) {
        row_count[trees[i][0]]++;
        col_count[trees[i][1]]++;
    }

    precompute_combinations(W, k);

    ull total_piety = 0;

    for (int i = 0; i < W; i++) {
        int x = trees[i][0], y = trees[i][1];
        int left = 0, right = 0, up = 0, down = 0;

        for (int j = 0; j < i; j++) {
            if (trees[j][0] == x && trees[j][1] < y) left++;
        }
        for (int j = i + 1; j < W; j++) {
            if (trees[j][0] == x && trees[j][1] > y) right++;
        }
        for (int j = 0; j < i; j++) {
            if (trees[j][1] == y && trees[j][0] < x) up++;
        }
        for (int j = i + 1; j < W; j++) {
            if (trees[j][1] == y && trees[j][0] > x) down++;
        }

        if (left >= k && right >= k && up >= k && down >= k) {
            ull piety = mod_mul(mod_mul(comb[left][k], comb[right][k]), mod_mul(comb[up][k], comb[down][k]));
            total_piety = mod_add(total_piety, piety);
        }
    }

    printf("%llu\n", total_piety);

    return 0;
}