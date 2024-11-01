#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a == b) {
        printf("1\n");
    } else {
        int g = a ^ b;
        if (g == 0) {
            printf("-1\n");
        } else {
            printf("1\n");
        }
    }
    return 0;
}