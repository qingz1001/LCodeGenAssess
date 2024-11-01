#include <stdio.h>

int main() {
    int n, count5 = 0, count0 = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        if (num == 5) {
            count5++;
        } else if (num == 0) {
            count0++;
        }
    }
    if (count5 == 0) {
        printf("-1\n");
    } else if (count5 % 2 == 0) {
        printf("0");
        for (int i = 0; i < count5 / 2; i++) {
            printf("55");
        }
        for (int i = 0; i < count0; i++) {
            printf("0");
        }
        printf("\n");
    } else if (count0 >= 2) {
        printf("0");
        for (int i = 0; i < count5 / 2; i++) {
            printf("55");
        }
        printf("0");
        for (int i = 0; i < count0 - 2; i++) {
            printf("0");
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
    return 0;
}