#include <stdio.h>
#include <math.h>

// 计算两个点之间的欧几里得距离
double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int M, n, k;
    scanf("%d %d %d", &M, &n, &k);

    int weapons[M][2]; // 存储武器的坐标
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &weapons[i][0], &weapons[i][1]);
    }

    int bombs[n][2]; // 存储炸弹的坐标
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bombs[i][0], &bombs[i][1]);
    }

    int bomb_used = 0; // 记录使用的炸弹数量
    int active_weapon = 0; // 当前处于攻击状态的武器编号

    while (active_weapon < M) {
        int best_bomb = -1;
        double best_distance = -1;

        // 找到距离当前武器最近的炸弹
        for (int i = 0; i < n; i++) {
            if (bomb_used <= i) { // 只考虑未使用的炸弹
                double dist = distance(weapons[active_weapon][0], weapons[active_weapon][1], bombs[i][0], bombs[i][1]);
                if (dist <= k && (best_bomb == -1 || dist < best_distance)) {
                    best_bomb = i;
                    best_distance = dist;
                }
            }
        }

        if (best_bomb == -1) {
            break; // 没有找到合适的炸弹，无法摧毁武器
        }

        bomb_used++;
        active_weapon++;

        // 如果是最后一个武器，连环阵被摧毁
        if (active_weapon == M) {
            break;
        }
    }

    printf("%d\n", bomb_used); // 输出实际使用的炸弹数量
    return 0;
}