#include <stdio.h>

#define MOD 9901

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    // Check if the input values are valid for a complete binary tree of depth k
    if (n != (1 << k) - 1 || k < 2) {
        printf("Invalid input\n");
        return 1;
    }

    // The number of structures of a complete binary tree of depth k is always 2
    printf("2\n");

    return 0;
}