#include <stdio.h>

// 定义每个数字所需的火柴棍数量
int matchsticks[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

// 计算一个数字所需的火柴棍数量
int countMatchsticks(int num) {
    int count = 0;
    while (num > 0) {
        count += matchsticks[num % 10];
        num /= 10;
    }
    return count;
}

int main() {
    int n, count = 0;
    scanf("%d", &n);

    // 减去加号和等号所需的火柴棍数量
    n -= 4;

    // 遍历所有可能的A和B
    for (int A = 0; A < 10000; A++) {
        for (int B = 0; B < 10000; B++) {
            int C = A + B;
            if (C >= 10000) continue; // C不能超过4位数

            // 计算A、B、C所需的火柴棍数量
            int matchsticks_A = countMatchsticks(A);
            int matchsticks_B = countMatchsticks(B);
            int matchsticks_C = countMatchsticks(C);

            // 如果火柴棍数量总和等于n，则计数
            if (matchsticks_A + matchsticks_B + matchsticks_C == n) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}