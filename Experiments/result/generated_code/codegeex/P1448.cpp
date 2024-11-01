#include <stdio.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_M 10000

int n, m;
bool bad[MAX_N + 1][2 * MAX_N]; // 存储被蛀虫咬坏的单元

void read_input() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        bad[x][y] = true;
    }
}

int main() {
    read_input();

    // 遍历所有可能的裁剪方式
    for (int x1 = 1; x1 <= n; x1++) {
        for (int y1 = 1; y1 <= 2 * x1 - 1; y1++) {
            for (int x2 = x1; x2 <= n; x2++) {
                int y2_min = (x2 == x1) ? y1 : 1;
                for (int y2 = y2_min; y2 <= 2 * x2 - 1; y2++) {
                    bool valid = true;
                    // 检查第一块围巾
                    for (int x = x1; x <= (x1 + x2) / 2; x++) {
                        for (int y = (x == x1) ? y1 : 1; y <= 2 * x - 1; y++) {
                            if (bad[x][y]) {
                                valid = false;
                                goto check_second;
                            }
                        }
                    }
                    // 检查第二块围巾
                    for (int x = (x1 + x2) / 2 + 1; x <= x2; x++) {
                        for (int y = (x == x2) ? y2 : 1; y <= 2 * x - 1; y++) {
                            if (bad[x][y]) {
                                valid = false;
                                goto check_second;
                            }
                        }
                    }
check_second:
                    if (valid) {
                        // 计算面积
                        int area1 = (x1 + x2) * (x1 + x2 + 1) / 2 - (x1 - 1) * x1 / 2;
                        int area2 = (x2 + x2) * (x2 + x2 + 1) / 2 - (x2 - 1) * x2 / 2;
                        int total_area = area1 + area2;
                        printf("%d\n", total_area);
                        return 0;
                    }
                }
            }
        }
    }
    printf("0\n");
    return 0;
}