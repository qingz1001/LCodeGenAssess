#include <stdio.h>
#include <stdlib.h>

void printFractions(int a, int b) {
    if (a == 0 || b <= a) {
        return;
    }
    int k = b / a + 1;
    printf("%d", k);
    if (k != b / a) {
        printf(" ");
    }
    printFractions(a * k - b, b * k);
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printFractions(a, b);
    return 0;
}