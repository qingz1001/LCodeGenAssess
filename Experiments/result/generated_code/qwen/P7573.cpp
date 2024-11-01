#include <stdio.h>

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (n == 1) {
            printf("0\n");
        } else {
            printf("%d\n", n - 1);
        }
    }
    return 0;
}