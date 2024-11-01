#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int x[700], y[700];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    int maxCount = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int count = 2; // 初始值为2，因为两个点一定在同一条直线上
            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    if ((x[i] - x[j]) * (y[i] - y[k]) == (x[i] - x[k]) * (y[i] - y[j])) {
                        count++;
                    }
                }
            }
            if (count > maxCount) {
                maxCount = count;
            }
        }
    }

    printf("%d\n", maxCount);

    return 0;
}