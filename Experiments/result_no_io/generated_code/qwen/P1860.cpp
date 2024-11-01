#include <stdio.h>
#include <stdlib.h>

#define MAX_N 60
#define MAX_M 240
#define MAX_K 30

int N, M, V, K;
int prices[MAX_N][2];
int spells[MAX_M][MAX_N];

void dfs(int index, int money, int used_spells) {
    if (index == N || used_spells >= K) {
        printf("%d\n", money);
        return;
    }

    // Use the current potion directly
    dfs(index + 1, money + prices[index][0] - prices[index][1], used_spells);

    // Try to use spells with the current potion as a raw material
    for (int i = 0; i < M; i++) {
        if (spells[i][0] != index + 1) continue;
        int num_ingredients = spells[i][1];
        int can_use = 1;
        for (int j = 2; j < 2 + num_ingredients; j++) {
            if (money < prices[spells[i][j] - 1][1]) {
                can_use = 0;
                break;
            }
        }
        if (can_use) {
            int new_money = money;
            for (int j = 2; j < 2 + num_ingredients; j++) {
                new_money -= prices[spells[i][j] - 1][1];
            }
            dfs(index + 1, new_money + prices[index][0] - prices[index][1], used_spells + 1);
        }
    }
}

int main() {
    scanf("%d %d %d %d", &N, &M, &V, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &prices[i][0], &prices[i][1]);
    }
    for (int i = 0; i < M; i++) {
        int finish, num_ingredients;
        scanf("%d %d", &finish, &num_ingredients);
        spells[i][0] = finish;
        spells[i][1] = num_ingredients;
        for (int j = 0; j < num_ingredients; j++) {
            scanf("%d", &spells[i][2 + j]);
        }
    }

    dfs(0, V, 0);

    return 0;
}