#include <stdio.h>
#include <math.h>

void print_triangle(int size, int row, int col) {
    if (size == 1) {
        printf("/\\");
    } else {
        int half_size = size / 2;
        if (row < half_size) {
            print_triangle(half_size, row, col);
        } else if (row == half_size) {
            printf("/");
            for (int i = 0; i < half_size; i++) printf("_");
            printf("\\");
        } else {
            print_triangle(half_size, row - half_size, col - half_size);
        }
    }
}

void print_pattern(int n) {
    int size = (int)pow(2, n);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size - row; col++) {
            print_triangle(size, row, col);
            printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    print_pattern(n);
    return 0;
}