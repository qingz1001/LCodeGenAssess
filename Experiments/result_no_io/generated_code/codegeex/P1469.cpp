#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int sum = 0;
    int single = 0;

    for (int i = 0; i < n; i++) {
        int length;
        scanf("%d", &length);
        sum += length;
    }

    single = sum / (n - 1); // 计算所有筷子总长度的平均值

    printf("%d\n", single);

    return 0;
}