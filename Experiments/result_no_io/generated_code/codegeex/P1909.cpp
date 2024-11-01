#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int pack1[2] = {2, 2}; // 2支装，价格为2
    int pack2[2] = {50, 30}; // 50支装，价格为30
    int pack3[2] = {30, 27}; // 30支装，价格为27

    int min_cost = INT_MAX;

    // 计算每种包装所需的最小花费
    for (int i = 1; i <= 3; i++) {
        int pack_size, pack_price;
        if (i == 1) {
            pack_size = pack1[0];
            pack_price = pack1[1];
        } else if (i == 2) {
            pack_size = pack2[0];
            pack_price = pack2[1];
        } else {
            pack_size = pack3[0];
            pack_price = pack3[1];
        }

        int num_packs = (n + pack_size - 1) / pack_size; // 向上取整
        int cost = num_packs * pack_price;

        if (cost < min_cost) {
            min_cost = cost;
        }
    }

    printf("%d\n", min_cost);

    return 0;
}