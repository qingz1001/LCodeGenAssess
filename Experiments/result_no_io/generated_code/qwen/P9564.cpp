#include <stdio.h>

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    if (A + B == 9 && A >= 1 && A <= 6 && B >= 1 && B <= 6) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}