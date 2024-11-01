#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int left = (a < b) ? a : b;
    int right = (a > b) ? a : b;

    if (left >= 0) {
        printf("%d\n", right);
    } else if (right <= 0) {
        printf("%d\n", -left);
    } else {
        printf("%d\n", right - left);
    }

    return 0;
}