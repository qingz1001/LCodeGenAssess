#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int* floors = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &floors[i]);
    }

    // 对楼层进行排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (floors[j] > floors[j + 1]) {
                int temp = floors[j];
                floors[j] = floors[j + 1];
                floors[j + 1] = temp;
            }
        }
    }

    int total_time = 0;
    int current_floor = 0;

    // 计算电梯运行时间
    for (int i = 0; i < n; i++) {
        total_time += abs(floors[i] - current_floor) * 2; // 上楼和下楼时间
        total_time += 5; // 开门时间
        total_time += 1; // 下一个人时间
        current_floor = floors[i];
    }

    // 电梯回到0层
    total_time += abs(current_floor) * 2;

    printf("%d\n", total_time);

    free(floors);
    return 0;
}