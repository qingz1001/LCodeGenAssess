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

void solve() {
    // Placeholder for the actual solution logic
    // This function should modify the grid to create a maze
    // that can hide the maximum number of children.
    // For now, it just prints the input grid as is.
}

int main() {
    read_input();
    solve();
    print_output();
    return 0;
}