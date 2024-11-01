#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

char grid[MAX_SIZE][MAX_SIZE];
int m, n, k;

void read_input() {
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }
}

void print_output() {
    for (int i = 0; i < m; i++) {
        printf("%s\n", grid[i]);
    }
}

void place_bushes() {
    // Place bushes to create a maze structure
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '.' && rand() % 2 == 0) {
                grid[i][j] = 'X';
            }
        }
    }
}

int main() {
    read_input();
    place_bushes();
    print_output();
    return 0;
}