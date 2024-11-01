#include <stdio.h>
#include <limits.h>

#define MAX_DISTANCE 10
#define TEAM_MEMBERS 5
#define TOTAL_DISTANCE 25

int main() {
    int times[TEAM_MEMBERS][MAX_DISTANCE + 1];
    int km[TEAM_MEMBERS];
    int min_time = INT_MAX;
    int best_km[TEAM_MEMBERS];

    // 读取输入
    for (int i = 0; i < TEAM_MEMBERS; i++) {
        for (int j = 1; j <= MAX_DISTANCE; j++) {
            scanf("%d", &times[i][j]);
        }
    }

    // 遍历所有可能的分配方案
    for (int i1 = 1; i1 <= MAX_DISTANCE; i1++) {
        for (int i2 = 1; i2 <= MAX_DISTANCE; i2++) {
            for (int i3 = 1; i3 <= MAX_DISTANCE; i3++) {
                for (int i4 = 1; i4 <= MAX_DISTANCE; i4++) {
                    for (int i5 = 1; i5 <= MAX_DISTANCE; i5++) {
                        if (i1 + i2 + i3 + i4 + i5 == TOTAL_DISTANCE) {
                            int time = times[0][i1] + times[1][i2] + times[2][i3] + times[3][i4] + times[4][i5];
                            if (time < min_time) {
                                min_time = time;
                                km[0] = i1;
                                km[1] = i2;
                                km[2] = i3;
                                km[3] = i4;
                                km[4] = i5;
                            }
                        }
                    }
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", min_time);
    for (int i = 0; i < TEAM_MEMBERS; i++) {
        printf("%d ", km[i]);
    }
    printf("\n");

    return 0;
}