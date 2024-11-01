#include <stdio.h>

void print_tatoo(int n) {
    int total_lines = 2 * n - 1;
    for (int i = 0; i < total_lines; i++) {
        int num_spaces = (total_lines - i - 1) / 2;
        int num_slashes = i + 1;
        int num_slashes_in_row = num_slashes;
        if (i >= n) {
            num_slashes_in_row = total_lines - i;
        }
        for (int j = 0; j < num_spaces; j++) {
            printf(" ");
        }
        for (int j = 0; j < num_slashes_in_row; j++) {
            if (j % 2 == 0) {
                printf("/");
            } else {
                printf("\\");
            }
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    print_tatoo(n);
    return 0;
}