#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int minDifference = 2000000000; // 初始化为一个很大的值
    for (int i = 0; i < n; i++) {
        int maxElement = a[i];
        int minElement = a[i];
        for (int j = i + 1; j < n; j++) {
            if (a[j] > maxElement) {
                maxElement = a[j];
            }
            if (a[j] < minElement) {
                minElement = a[j];
            }
            int difference = maxElement - minElement;
            if (difference < minDifference) {
                minDifference = difference;
            }
        }
    }

    printf("%d\n", minDifference);
    return 0;
}