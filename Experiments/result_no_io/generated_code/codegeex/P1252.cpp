#include <stdio.h>
#include <limits.h>

int main() {
    int time[5][10];
    int min_time = INT_MAX;
    int min_time_arrangement[5];
    int arrangement[5];
    int i, j, k, l, m;

    // 输入每个运动员的跑步时间
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            scanf("%d", &time[i][j]);
        }
    }

    // 搜索所有可能的安排
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (i + j > 10) break;
            for (k = 0; k < 10; k++) {
                if (i + j + k > 10) break;
                for (l = 0; l < 10; l++) {
                    if (i + j + k + l > 10) break;
                    for (m = 0; m < 10; m++) {
                        if (i + j + k + l + m > 10) break;
                        int total_time = time[0][i] + time[1][j] + time[2][k] + time[3][l] + time[4][m];
                        if (total_time < min_time) {
                            min_time = total_time;
                            arrangement[0] = i;
                            arrangement[1] = j;
                            arrangement[2] = k;
                            arrangement[3] = l;
                            arrangement[4] = m;
                        }
                    }
                }
            }
        }
    }

    // 输出最短时间
    printf("%d\n", min_time);

    // 输出每个运动员跑的公里数
    for (i = 0; i < 5; i++) {
        printf("%d ", arrangement[i]);
    }
    printf("\n");

    return 0;
}