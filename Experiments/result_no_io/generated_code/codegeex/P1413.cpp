#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int zombie[2000][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &zombie[i][0], &zombie[i][1]);
    }

    int nuts = 0;
    int lastNutTime[6] = {0}; // 记录每行上次放置坚果的时间

    for (int i = 0; i < n; i++) {
        int row = zombie[i][0] - 1; // 行号从1到6，转换为0到5
        int time = zombie[i][1];

        if (time - lastNutTime[row] >= 10) {
            nuts++;
            lastNutTime[row] = time;
        }
    }

    printf("%d\n", nuts);
    return 0;
}