#include <stdio.h>

void printFigure(int n) {
    if (n == 1) {
        printf("   /\\\n  /  \\\n /____\\\n");
    } else {
        printFigure(n - 1);
        printf(" /");
        for (int i = 0; i < 4 * (n - 1); i++) {
            printf(" ");
        }
        printf("\\ \n");
        printf("/");
        for (int i = 0; i < 4 * (n - 1); i++) {
            printf(" ");
        }
        printf(" \\\n");
        printFigure(n - 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printFigure(n);
    return 0;
}