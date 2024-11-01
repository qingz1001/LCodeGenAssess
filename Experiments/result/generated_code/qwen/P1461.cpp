#include <stdio.h>
#include <stdlib.h>

#define MAX_N 64
#define MAX_B 8
#define MAX_D 7

int n, b, d;
int codes[MAX_N];

// 计算两个数的汉明距离
int hamming_distance(int a, int b) {
    int xor_result = a ^ b;
    int distance = 0;
    while (xor_result != 0) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }
    return distance;
}

// 检查当前编码是否满足条件
int check_code(int code) {
    for (int i = 0; i < n; i++) {
        if (i != code && hamming_distance(codes[i], code) < d) {
            return 0;
        }
    }
    return 1;
}

// 生成编码
void generate_codes() {
    for (int i = 0; i < n; i++) {
        codes[i] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!check_code(codes[j])) {
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    codes[k]++;
                }
                i--;
                break;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &b, &d);
    generate_codes();
    for (int i = 0; i < n; i++) {
        printf("%d ", codes[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    return 0;
}