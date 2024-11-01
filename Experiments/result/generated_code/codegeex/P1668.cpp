#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25000
#define MAX_T 1000000

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    int start[MAX_N], end[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }

    // 对奶牛的值班时间段进行排序
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (start[i] > start[j]) {
                int temp = start[i];
                start[i] = start[j];
                start[j] = temp;
                temp = end[i];
                end[i] = end[j];
                end[j] = temp;
            }
        }
    }

    // 使用贪心算法安排值班
    int last_end = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (start[i] > last_end) {
            count++;
            last_end = end[i];
        }
    }

    printf("%d\n", count);

    return 0;
}