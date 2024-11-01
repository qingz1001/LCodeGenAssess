#include <stdio.h>
#include <stdbool.h>

#define MAX 41

// 函数声明
double triangleArea(double a, double b, double c);
bool checkTriangle(double a, double b, double c);

int main() {
    int n;
    scanf("%d", &n);
    int lengths[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    // 按长度排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lengths[i] > lengths[j]) {
                int temp = lengths[i];
                lengths[i] = lengths[j];
                lengths[j] = temp;
            }
        }
    }

    int maxArea = -1;
    // 尝试所有可能的三角形组合
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (checkTriangle(lengths[i], lengths[j], lengths[k])) {
                    double area = triangleArea(lengths[i], lengths[j], lengths[k]);
                    int intArea = (int)(area * 100);
                    if (intArea > maxArea) {
                        maxArea = intArea;
                    }
                }
            }
        }
    }

    printf("%d\n", maxArea);
    return 0;
}

// 计算三角形面积
double triangleArea(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// 检查是否能构成三角形
bool checkTriangle(double a, double b, double c) {
    if (a + b > c && a + c > b && b + c > a) {
        return true;
    }
    return false;
}