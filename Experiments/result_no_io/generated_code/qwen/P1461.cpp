#include <stdio.h>
#include <stdlib.h>

#define MAX_N 64
#define MAX_B 8
#define MAX_D 7

int n, b, d;
int codes[MAX_N];

// 计算两个整数之间的汉明距离
int hamming_distance(int a, int b) {
    int xor_result = a ^ b;
    int distance = 0;
    while (xor_result > 0) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }
    return distance;
}

// 检查当前编码是否满足条件
int check_code(int code) {
    for (int i = 0; i < n - 1; i++) {
        if (hamming_distance(code, codes[i]) < d) {
            return 0;
        }
    }
    return 1;
}

// 生成所有可能的编码并检查它们
void generate_codes() {
    for (int i = 0; i < (1 << b); i++) {
        if (check_code(i)) {
            codes[n++] = i;
        }
        if (n == MAX_N) break;
    }
}

int main() {
    scanf("%d %d %d", &n, &b, &d);
    generate_codes();
    qsort(codes, n, sizeof(int), (int (*)(const void *, const void *))compare);

    for (int i = 0; i < n; i++) {
        printf("%d ", codes[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }

    return 0;
}