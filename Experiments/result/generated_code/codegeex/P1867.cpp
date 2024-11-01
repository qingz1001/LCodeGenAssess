#include <stdio.h>
#include <math.h>

int main() {
    int n, i;
    double life = 10.0, total_exp = 0.0;
    double exp;

    // 读取操作次数
    scanf("%d", &n);

    // 处理每次操作
    for (i = 0; i < n; i++) {
        double x, a;
        scanf("%lf %lf", &x, &a);

        // 更新生命值
        life -= x;
        if (life <= 0) {
            break;  // 生命值小于等于0，停止后续操作
        }
        if (life > 10) {
            life = 10;  // 生命值上限为10
        }

        // 累加经验值
        total_exp += a;
    }

    // 计算等级
    int level = 0;
    while (total_exp >= pow(2, level)) {
        total_exp -= pow(2, level);
        level++;
    }

    // 输出结果
    printf("%d %lf\n", level, total_exp);

    return 0;
}