#include <stdio.h>

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    if (A + B == 9 && A >= 0 && A <= 9 && B >= 0 && B <= 9) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}