#include <stdio.h>
#include <stdlib.h>

#define MAX_N 60
#define MAX_M 240
#define MAX_K 30

int N, M, V, K;
int potions[MAX_N][2];
int spells[MAX_M][MAX_N + 1];

int max(int a, int b) {
    return (a > b) ? a : b;
}

void dfs(int index, int money, int used_spells[], int *max_profit) {
    if (index == N || used_spells[index] >= K) {
        *max_profit = max(*max_profit, money);
        return;
    }

    // Don't use the current potion
    dfs(index + 1, money, used_spells, max_profit);

    // Use the current potion
    if (money >= potions[index][1]) {
        int new_money = money - potions[index][1] + potions[index][0];
        used_spells[index]++;
        dfs(index + 1, new_money, used_spells, max_profit);
        used_spells[index]--;
    }
}

int main() {
    scanf("%d %d %d %d", &N, &M, &V, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &potions[i][0], &potions[i][1]);
    }
    for (int i = 0; i < M; i++) {
        int成品, 原料数;
        scanf("%d %d", &成品, &原料数);
        spells[i][0] = 成品;
        for (int j = 1; j <= 原料数; j++) {
            scanf("%d", &spells[i][j]);
        }
    }

    int max_profit = 0;
    int used_spells[MAX_N] = {0};
    dfs(0, V, used_spells, &max_profit);

    printf("%d\n", max_profit);

    return 0;
}