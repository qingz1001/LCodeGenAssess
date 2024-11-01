#include <stdio.h>
#include <stdlib.h>

// 计算绝对值
int abs(int x) {
    return x > 0 ? x : -x;
}

// 计算最大公约数
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 计算最小公倍数
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

// 检查是否可以通过跳动达到目标状态
int check(int a, int b, int c, int x, int y, int z) {
    int a1 = abs(x - y), b1 = abs(y - z), c1 = abs(x - z);
    int a2 = abs(a - b), b2 = abs(b - c), c2 = abs(a - c);
    int lcm_ab = lcm(a1, a2), lcm_bc = lcm(b1, b2), lcm_ac = lcm(c1, c2);
    if (lcm_ab != lcm_bc || lcm_bc != lcm_ac) return 0;
    return 1;
}

int main() {
    int a, b, c, x, y, z;
    scanf("%d%d%d", &a, &b, &c);
    scanf("%d%d%d", &x, &y, &z);

    // 对输入的坐标进行排序
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b > c) {
        int temp = b;
        b = c;
        c = temp;
    }
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }
    if (y > z) {
        int temp = y;
        y = z;
        z = temp;
    }
    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }

    // 检查是否可以通过跳动达到目标状态
    if (check(a, b, c, x, y, z)) {
        printf("YES\n");
        // 计算最少步数
        int steps = abs(a - x) + abs(b - y) + abs(c - z) - 3;
        printf("%d\n", steps);
    } else {
        printf("NO\n");
    }

    return 0;
}