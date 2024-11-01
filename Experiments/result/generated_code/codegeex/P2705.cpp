#include <stdio.h>

int main() {
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);

    int max_score = 0;

    // 当红球和蓝球数量相等时，直接按颜色放球，得分就是C * R + D * B
    if (R == B) {
        max_score = C * R + D * B;
    } else {
        // 当红球和蓝球数量不相等时，需要考虑将不同颜色的球混合放置的情况
        if (R > B) {
            // 如果红球多，优先放置红球到红盒中，剩余的蓝球放蓝盒中
            max_score = C * R + D * B;
            // 尝试将一些红球放置到蓝盒中，看是否得分更高
            for (int i = 1; i <= R - B; i++) {
                int current_score = (C - E) * (R - B - i) + (D - E) * B + E * i;
                if (current_score > max_score) {
                    max_score = current_score;
                }
            }
        } else {
            // 如果蓝球多，优先放置蓝球到蓝盒中，剩余的红球放红盒中
            max_score = C * R + D * B;
            // 尝试将一些蓝球放置到红盒中，看是否得分更高
            for (int i = 1; i <= B - R; i++) {
                int current_score = (C - E) * R + (D - E) * (B - R - i) + E * i;
                if (current_score > max_score) {
                    max_score = current_score;
                }
            }
        }
    }

    printf("%d\n", max_score);
    return 0;
}