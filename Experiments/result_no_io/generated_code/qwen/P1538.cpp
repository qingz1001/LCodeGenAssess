#include <stdio.h>
#include <string.h>

void printDigit(int digit, int size) {
    if (digit == 0) {
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
    } else if (digit == 1) {
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
    } else if (digit == 2) {
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|__|");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|__|");
        }
        printf("\n");
    } else if (digit == 3) {
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
    } else if (digit == 4) {
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|  |");
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|  |");
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("|  |");
        printf("\n");
    } else if (digit == 5) {
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|__|");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|__|");
        }
        printf("\n");
    } else if (digit == 6) {
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|__|");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
    } else if (digit == 7) {
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
    } else if (digit == 8) {
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
    } else if (digit == 9) {
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf(" __ ");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("|  |");
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            printf("   ");
        }
        printf("\n");
    }
}

int main() {
    int k;
    scanf("%d", &k);
    char s[256];
    scanf("%s", s);

    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        if (i != 0) {
            for (int j = 0; j < k; j++) {
                printf(" ");
            }
        }
        printDigit(s[i] - '0', k);
    }

    return 0;
}