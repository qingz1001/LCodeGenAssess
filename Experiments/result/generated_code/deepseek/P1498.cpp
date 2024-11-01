#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_pattern(int n, int row, int col, char **pattern) {
    if (n == 1) {
        pattern[row][col] = '/';
        pattern[row][col + 1] = '\\';
        pattern[row + 1][col - 1] = '/';
        pattern[row + 1][col] = '_';
        pattern[row + 1][col + 1] = '_';
        pattern[row + 1][col + 2] = '\\';
    } else {
        print_pattern(n - 1, row, col, pattern);
        print_pattern(n - 1, row + (1 << (n - 1)), col - (1 << (n - 1)), pattern);
        print_pattern(n - 1, row + (1 << (n - 1)), col + (1 << (n - 1)), pattern);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int size = 1 << n; // 2^n
    char **pattern = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        pattern[i] = (char *)malloc((2 * size) * sizeof(char));
        memset(pattern[i], ' ', 2 * size);
    }

    print_pattern(n, 0, (1 << (n - 1)) - 1, pattern);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 2 * size; j++) {
            printf("%c", pattern[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < size; i++) {
        free(pattern[i]);
    }
    free(pattern);

    return 0;
}