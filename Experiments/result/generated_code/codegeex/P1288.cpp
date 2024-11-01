#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[30];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 检查是否所有的边上的数都是0
    int all_zeros = 1;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            all_zeros = 0;
            break;
        }
    }

    if (all_zeros) {
        printf("NO\n");
    } else {
        printf("YES\n");
    }

    return 0;
}