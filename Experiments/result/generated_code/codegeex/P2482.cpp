#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 10
#define MAX_HANDCARDS 2000

char roles[MAX_PLAYERS][5];
char handcards[MAX_PLAYERS][MAX_HANDCARDS];
int n, m;
int handcard_counts[MAX_PLAYERS];
int health[MAX_PLAYERS];
int position[MAX_PLAYERS];
int alive[MAX_PLAYERS];

void init() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %s %s", roles[i], handcards[i], handcards[i] + 5, handcards[i] + 10, handcards[i] + 15);
        handcard_counts[i] = 4;
        health[i] = 4;
        position[i] = i;
        alive[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        scanf("%s", handcards[i]);
    }
}

int main() {
    init();
    // 游戏主循环
    while (1) {
        // 检查游戏是否结束
        int mp_alive = 0;
        int fp_alive = 0;
        for (int i = 0; i < n; i++) {
            if (alive[i]) {
                if (strcmp(roles[i], "MP") == 0) {
                    mp_alive = 1;
                }
                if (strcmp(roles[i], "FP") == 0) {
                    fp_alive = 1;
                }
            }
        }
        if (!mp_alive) {
            printf("FP\n");
            for (int i = 0; i < n; i++) {
                if (alive[i]) {
                    printf("%s\n", handcards[i]);
                } else {
                    printf("DEAD\n");
                }
            }
            return 0;
        }
        if (!fp_alive) {
            printf("MP\n");
            for (int i = 0; i < n; i++) {
                if (alive[i]) {
                    printf("%s\n", handcards[i]);
                } else {
                    printf("DEAD\n");
                }
            }
            return 0;
        }

        // 玩家行动
        for (int i = 0; i < n; i++) {
            if (!alive[i]) continue;
            // 摸牌阶段
            for (int j = 0; j < 2; j++) {
                if (m > 0) {
                    handcards[i][handcard_counts[i]++] = handcards[m - 1];
                    m--;
                } else {
                    handcards[i][handcard_counts[i]++] = handcards[m - 1];
                }
            }

            // 出牌阶段
            // TODO: 实现出牌逻辑
        }
    }
    return 0;
}