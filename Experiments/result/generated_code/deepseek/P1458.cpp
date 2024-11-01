#include <stdio.h>
#include <stdlib.h>

// 计算最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 比较两个分数的大小
int compare(int a1, int b1, int a2, int b2) {
    return a1 * b2 - a2 * b1;
}

int main() {
    int n;
    scanf("%d", &n);

    // 存储所有分数的分子和分母
    int fractions[160 * 160][2];
    int count = 0;

    // 生成所有满足条件的分数
    for (int b = 1; b <= n; b++) {
        for (int a = 0; a <= b; a++) {
            if (gcd(a, b) == 1) {
                fractions[count][0] = a;
                fractions[count][1] = b;
                count++;
            }
        }
    }

    // 使用冒泡排序对分数进行排序
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (compare(fractions[j][0], fractions[j][1], fractions[j + 1][0], fractions[j + 1][1]) > 0) {
                int temp[2];
                temp[0] = fractions[j][0];
                temp[1] = fractions[j][1];
                fractions[j][0] = fractions[j + 1][0];
                fractions[j][1] = fractions[j + 1][1];
                fractions[j + 1][0] = temp[0];
                fractions[j + 1][1] = temp[1];
            }
        }
    }

    // 输出排序后的分数
    for (int i = 0; i < count; i++) {
        printf("%d/%d\n", fractions[i][0], fractions[i][1]);
    }

    return 0;
}