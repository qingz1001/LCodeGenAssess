#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int wall[N+1] = {0}; // 初始化electoral墙，长度为N+1，便于处理边界情况

    // 读取每张海报的信息，并更新electoral墙
    for (int i = 0; i < M; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        wall[A]++;
        wall[B+1]--;
    }

    // 计算electoral墙上还能看见的海报数
    int visible_posters = 0;
    int current_posters = 0;
    for (int i = 1; i <= N; i++) {
        current_posters += wall[i];
        if (current_posters > 0) {
            visible_posters++;
        }
    }

    printf("%d\n", visible_posters);
    return 0;
}