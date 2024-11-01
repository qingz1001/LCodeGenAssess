#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int wall[N + 1] = {0}; // 初始化electoral墙的数组

    // 处理每张海报
    for (int i = 0; i < M; i++) {
        int A, B;
        scanf("%d %d", &A, &B);

        // 将海报的起始和结束位置标记为1
        wall[A]++;
        wall[B + 1]--;
    }

    int visible_posters = 0;
    int current_posters = 0;

    // 计算electoral墙上可见的海报数
    for (int i = 1; i <= N; i++) {
        current_posters += wall[i];
        if (current_posters > 0) {
            visible_posters++;
        }
    }

    printf("%d\n", visible_posters);
    return 0;
}