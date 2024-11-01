#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    for (int i = n; i > 0; i--) {
        if ((i & (i - 1)) == 0) {
            printf("%d ", i);
            n -= i;
            if (n == 0) {
                break;
            }
        }
    }

    if (n != 0) {
        printf("-1\n");
    } else {
        printf("\n");
    }

    return 0;
}