#include <stdio.h>

int main() {
    int a, b, c;
    char order[4];

    // 读取输入的三个整数
    scanf("%d%d%d", &a, &b, &c);
    // 读取输入的顺序
    scanf("%s", order);

    // 根据输入的顺序输出对应的整数
    if (order[0] == 'A') {
        if (order[1] == 'B') {
            if (order[2] == 'C') {
                printf("%d %d %d\n", a, b, c);
            } else {
                printf("%d %d %d\n", a, c, b);
            }
        } else {
            if (order[2] == 'B') {
                printf("%d %d %d\n", a, b, c);
            } else {
                printf("%d %d %d\n", a, c, b);
            }
        }
    } else if (order[0] == 'B') {
        if (order[1] == 'A') {
            if (order[2] == 'C') {
                printf("%d %d %d\n", b, a, c);
            } else {
                printf("%d %d %d\n", b, c, a);
            }
        } else {
            if (order[2] == 'A') {
                printf("%d %d %d\n", b, a, c);
            } else {
                printf("%d %d %d\n", b, c, a);
            }
        }
    } else {
        if (order[1] == 'A') {
            if (order[2] == 'B') {
                printf("%d %d %d\n", c, a, b);
            } else {
                printf("%d %d %d\n", c, b, a);
            }
        } else {
            if (order[2] == 'A') {
                printf("%d %d %d\n", c, a, b);
            } else {
                printf("%d %d %d\n", c, b, a);
            }
        }
    }

    return 0;
}