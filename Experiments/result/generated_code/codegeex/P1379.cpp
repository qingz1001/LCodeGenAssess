#include <stdio.h>
#include <string.h>

int visited[362887] = {0}; // 记录状态是否访问过
int dist[362887] = {0}; // 记录状态距离起点的距离
int zero = 0; // 记录空格位置
int target = 123804765; // 目标状态
int dx[4] = {-3, 3, -1, 1}; // 四个方向的移动
int num[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 1-8的数字

// 判断是否达到目标状态
int is_target(int state) {
    return state == target;
}

// 计算状态字符串中空格的位置
int find_zero(int state) {
    int pos = 0;
    while ((state & 1) == 0) {
        state >>= 1;
        pos++;
    }
    return pos;
}

// 判断状态是否合法
int is_valid(int state) {
    int count = 0;
    while (state) {
        int bit = state & 1;
        if (bit) {
            count++;
        }
        state >>= 1;
    }
    return count == 9;
}

// 广度优先搜索
int bfs(int start) {
    int front = 0, rear = 0;
    int queue[362887] = {0};
    queue[rear++] = start;
    visited[start] = 1;
    dist[start] = 0;

    while (front < rear) {
        int state = queue[front++];
        int zero = find_zero(state);
        for (int i = 0; i < 4; i++) {
            int new_state = state;
            int new_zero = zero + dx[i];
            if (new_zero < 0 || new_zero >= 9 || (new_zero % 3 == 0 && dx[i] == -1) || (new_zero % 3 != 0 && dx[i] == 1)) {
                continue;
            }
            int temp = (new_state >> new_zero) & 1;
            new_state &= ~(1 << new_zero);
            new_state |= temp << zero;
            if (visited[new_state]) {
                continue;
            }
            visited[new_state] = 1;
            dist[new_state] = dist[state] + 1;
            queue[rear++] = new_state;
            if (is_target(new_state)) {
                return dist[new_state];
            }
        }
    }
    return -1;
}

int main() {
    int start = 0;
    char input[10];
    scanf("%s", input);
    for (int i = 0; i < 9; i++) {
        start |= (input[i] - '0') << (i * 4);
    }
    if (!is_valid(start)) {
        printf("0\n");
        return 0;
    }
    int result = bfs(start);
    printf("%d\n", result);
    return 0;
}