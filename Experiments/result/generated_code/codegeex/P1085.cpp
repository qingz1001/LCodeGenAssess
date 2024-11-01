#include <stdio.h>

int main() {
    int school_hours[7], extra_hours[7], total_hours[7];
    int max_hours = 0, max_day = 0;

    // 读取输入
    for (int i = 0; i < 7; i++) {
        scanf("%d %d", &school_hours[i], &extra_hours[i]);
        total_hours[i] = school_hours[i] + extra_hours[i];
    }

    // 检查每一天的总上课时间
    for (int i = 0; i < 7; i++) {
        if (total_hours[i] > 8) {
            if (total_hours[i] > max_hours) {
                max_hours = total_hours[i];
                max_day = i + 1; // 周一到周日分别对应1到7
            }
        }
    }

    // 输出结果
    printf("%d\n", max_day);

    return 0;
}