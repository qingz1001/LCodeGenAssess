#include <stdio.h>

void printTatoo(int size) {
    for (int i = 0; i < size; ++i) {
        // Print leading spaces
        for (int j = 0; j < size - i - 1; ++j) {
            printf(" ");
        }
        // Print the upper part of the tee-toe
        for (int j = 0; j <= 2 * i; ++j) {
            if (j == 0 || j == 2 * i) {
                printf("/");
            } else {
                printf("\\");
            }
        }
        // Move to the next line
        printf("\n");
    }
    // Print the middle part of the tee-toe
    for (int i = 0; i < size; ++i) {
        // Print leading spaces
        for (int j = 0; j < size - i - 1; ++j) {
            printf(" ");
        }
        // Print the middle part of the tee-toe
        for (int j = 0; j <= 2 * i; ++j) {
            if (j == 0 || j == 2 * i) {
                printf("_");
            } else {
                printf("|");
            }
        }
        // Move to the next line
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printTatoo(n);
    return 0;
}