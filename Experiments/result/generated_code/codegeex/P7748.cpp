#include <stdio.h>

int main() {
    int k, n, time = 0;
    char answer;

    // 读取游戏开始时拿箱人的编号和问题的数量
    scanf("%d %d", &k, &n);

    // 遍历每一个问题
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d %c", &t, &answer);

        // 累加回答该问题所用的时间
        time += t;

        // 如果时间达到或超过210秒，输出当前拿箱人的编号并结束程序
        if (time >= 210) {
            printf("%d\n", k);
            return 0;
        }

        // 如果回答正确，传递箱子给左手边第一个人
        if (answer == 'T') {
            k = (k % 8) + 1;
        }
    }

    // 如果时间没有达到210秒，输出最后一个拿箱人的编号
    printf("%d\n", k);
    return 0;
}