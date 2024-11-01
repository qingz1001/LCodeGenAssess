#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 定义武器和炸弹的结构体
typedef struct {
    int x, y;
} Weapon, Bomb;

// 计算两点之间的距离
double distance(Weapon a, Weapon b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int M, n, k;
    scanf("%d %d %d", &M, &n, &k);

    // 分配内存存储武器和炸弹的坐标
    Weapon *weapons = (Weapon *)malloc(M * sizeof(Weapon));
    Bomb *bombs = (Bomb *)malloc(n * sizeof(Bomb));

    // 读取武器的坐标
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &weapons[i].x, &weapons[i].y);
    }

    // 读取炸弹的坐标
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }

    // 初始化变量
    int bomb_used = 0;
    int weapon_active = 0;

    // 模拟引爆炸弹的过程
    while (weapon_active < M) {
        // 找到当前炸弹可以消灭的武器数量
        int weapons_destroyed = 0;
        for (int i = 0; i < M; i++) {
            if (distance(bombs[bomb_used], weapons[i]) <= k && weapons[i].x != -1) {
                weapons_destroyed++;
                weapons[i].x = -1; // 标记武器被消灭
            }
        }

        // 如果当前炸弹消灭了至少一个武器，则连环阵中的武器数量减少
        if (weapons_destroyed > 0) {
            weapon_active += weapons_destroyed;
        }

        // 更新使用的炸弹数量
        bomb_used++;
    }

    // 输出实际使用的炸弹数量
    printf("%d\n", bomb_used);

    // 释放分配的内存
    free(weapons);
    free(bombs);

    return 0;
}