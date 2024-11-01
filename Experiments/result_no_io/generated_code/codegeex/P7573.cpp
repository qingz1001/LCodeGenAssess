#include <stdio.h>

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (n == 1) {
            printf("0\n");
        } else if (n % 2 == 0) {
            printf("%d\n", n / 2);
        } else {
            printf("%d\n", n);
        }
    }
    return 0;
}