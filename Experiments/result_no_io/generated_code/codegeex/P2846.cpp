#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int a[MAXN]; // 用于记录灯的状态，1表示亮，0表示灭

void flip(int start, int end) {
    for (int i = start; i <= end; i++) {
        a[i] = 1 - a[i]; // 翻转灯的状态
    }
}

int countOn(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (a[i]) {
            count++; // 统计亮着的灯的数量
        }
    }
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        a[i] = 0; // 初始化所有灯的状态为灭
    }

    for (int i = 0; i < m; i++) {
        int command, start, end;
        scanf("%d %d %d", &command, &start, &end);
        if (command == 0) {
            flip(start, end); // 执行翻转操作
        } else if (command == 1) {
            printf("%d\n", countOn(start, end)); // 输出区间内亮着的灯的数量
        }
    }

    return 0;
}