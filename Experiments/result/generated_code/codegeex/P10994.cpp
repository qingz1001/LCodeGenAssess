#include <stdio.h>
#include <string.h>

int main() {
    int a, b;
    char s[100005];
    int num1 = 0, num2 = 0, num3 = 0, num4 = 0;

    // 读取学生和老师的人数
    scanf("%d%d", &a, &b);
    // 读取座位的类型字符串
    scanf("%s", s);

    // 遍历字符串，统计学生和老师的座位数量
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == 'S') {
            num1++;  // 统计学生座位
        } else {
            num2++;  // 统计教师座位
        }
    }

    // 检查是否有足够的座位给所有人
    if (num1 < a || num2 < b) {
        printf("-1\n");
        return 0;
    }

    // 计算将教师座位改为学生座位和将学生座位改为教师座位的次数
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == 'S') {
            num3++;  // 统计当前学生座位中能坐老师的数量
        } else {
            num4++;  // 统计当前教师座位中能坐学生的数量
        }
    }

    // 输出最少需要修改的次数
    printf("%d\n", (a - num3) + (b - num4));
    return 0;
}