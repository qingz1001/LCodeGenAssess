#include <stdio.h>

int main() {
    long long X;
    scanf("%lld", &X);

    int direction = 1; // 初始方向为正向
    int current_person = 1; // 初始报数人为1号

    for (long long i = 1; i <= X; i++) {
        if (i % 7 == 0 || i % 10 == 7 || (i / 10) % 10 == 7 || (i / 100) % 10 == 7 || (i / 1000) % 10 == 7) {
            direction = -direction; // 如果报的数是7的倍数或含有7，方向取反
        }
        current_person += direction; // 根据当前方向更新报数人

        if (current_person > 1337) {
            current_person = 1; // 如果当前报数人编号超过1337，回到1号人
        } else if (current_person < 1) {
            current_person = 1337; // 如果当前报数人编号小于1，回到1337号人
        }
    }

    printf("%d\n", current_person); // 输出最终报数的人的编号
    return 0;
}