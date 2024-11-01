#include <stdio.h>

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    int total_pips = A + B;
    if (total_pips % 2 == 0 && total_pips <= 18 && total_pips >= 3) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}