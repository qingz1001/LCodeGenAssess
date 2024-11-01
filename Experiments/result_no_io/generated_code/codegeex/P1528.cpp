#include <stdio.h>

int main() {
    int n, m;
    scanf("%d", &n);
    int cakes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }
    scanf("%d", &m);
    int mouths[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &mouths[i]);
    }

    // 对蛋糕和嘴巴的大小进行排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (cakes[j] > cakes[j + 1]) {
                int temp = cakes[j];
                cakes[j] = cakes[j + 1];
                cakes[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (mouths[j] > mouths[j + 1]) {
                int temp = mouths[j];
                mouths[j] = mouths[j + 1];
                mouths[j + 1] = temp;
            }
        }
    }

    int count = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (cakes[i] >= mouths[j]) {
            count++;
            i++;
            j++;
        } else {
            i++;
        }
    }

    printf("%d\n", count);
    return 0;
}