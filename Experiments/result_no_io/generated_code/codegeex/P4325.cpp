#include <stdio.h>

int main() {
    int a[10];
    int b[42] = {0}; // Array to keep track of distinct modulo values
    int count = 0;

    // Read 10 integers
    for (int i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }

    // Calculate modulo 42 for each integer and count distinct values
    for (int i = 0; i < 10; i++) {
        int mod_value = a[i] % 42;
        if (b[mod_value] == 0) {
            b[mod_value] = 1;
            count++;
        }
    }

    // Output the number of distinct values
    printf("%d\n", count);

    return 0;
}