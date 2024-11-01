#include <stdio.h>
#include <stdlib.h>

#define MAX_N 60
#define MAX_M 240

typedef struct {
    int sell_price;
    int buy_price;
} Potion;

typedef struct {
    int result;
    int num_ingredients;
    int ingredients[MAX_N];
} Magic;

int main() {
    int N, M, V, K;
    Potion potions[MAX_N];
    Magic magics[MAX_M];

    // 读取输入
    scanf("%d %d %d %d", &N, &M, &V, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &potions[i].sell_price, &potions[i].buy_price);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &magics[i].result, &magics[i].num_ingredients);
        for (int j = 0; j < magics[i].num_ingredients; j++) {
            scanf("%d", &magics[i].ingredients[j]);
        }
    }

    // 输出输入
    printf("%d %d %d %d\n", N, M, V, K);
    for (int i = 0; i < N; i++) {
        printf("%d %d\n", potions[i].sell_price, potions[i].buy_price);
    }
    for (int i = 0; i < M; i++) {
        printf("%d %d", magics[i].result, magics[i].num_ingredients);
        for (int j = 0; j < magics[i].num_ingredients; j++) {
            printf(" %d", magics[i].ingredients[j]);
        }
        printf("\n");
    }

    return 0;
}