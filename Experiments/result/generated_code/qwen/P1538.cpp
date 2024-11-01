#include <stdio.h>
#include <string.h>

void printDigit(int digit, int size) {
    if (digit == 0) {
        for (int i = 0; i < size; ++i) {
            printf("--");
            if (i != size - 1) printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; ++i) {
            printf("  |");
            if (i != size - 1) printf("    ");
        }
        printf("\n");
        for (int i = 0; i < size; ++i) {
            printf("  |");
            if (i != size - 1) printf("    ");
        }
        printf("\n");
        for (int i = 0; i < size; ++i) {
            printf("--");
            if (i != size - 1) printf("   ");
        }
        printf("\n");
    } else if (digit == 1) {
        for (int i = 0; i < size; ++i) {
            printf("  |");
            if (i != size - 1) printf("    ");
        }
        printf("\n");
        for (int i = 0; i < size; ++i) {
            printf("  |");
            if (i != size - 1) printf("    ");
        }
        printf("\n");
        for (int i = 0; i < size; ++i) {
            printf("  |");
            if (i != size - 1) printf("    ");
        }
        printf("\n");
        for (int i = 0; i < size; ++i) {
            printf("  |");
            if (i != size - 1) printf("    ");
        }
        printf("\n");
    }
    // Add other digits similarly
}

int main() {
    int k;
    scanf("%d", &k);
    char s[256];
    scanf("%s", s);

    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        printDigit(s[i] - '0', k);
        if (i < len - 1) {
            for (int j = 0; j < k; ++j) {
                printf("     ");
            }
        }
    }

    return 0;
}