#include <stdio.h>
#include <string.h>

void rotate90(char grid[11][11], char rotated[11][11], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotated[j][n - 1 - i] = grid[i][j];
        }
    }
}

void reflect(char grid[11][11], char reflected[11][11], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            char temp = grid[i][j];
            reflected[i][j] = grid[i][n - 1 - j];
            reflected[i][n - 1 - j] = temp;
        }
    }
}

int compare(char grid1[11][11], char grid2[11][11], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid1[i][j] != grid2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    char initial[11][11], final[11][11];
    
    for (int i = 0; i < n; i++) {
        scanf("%s", initial[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%s", final[i]);
    }
    
    char rotated90[11][11], rotated180[11][11], rotated270[11][11];
    char reflected[11][11];
    
    rotate90(initial, rotated90, n);
    rotate90(rotated90, rotated180, n);
    rotate90(rotated180, rotated270, n);
    reflect(initial, reflected, n);
    
    if (compare(final, initial, n)) {
        printf("6\n");
    } else if (compare(final, reflected, n)) {
        printf("4\n");
    } else if (compare(final, rotated90, n)) {
        printf("1\n");
    } else if (compare(final, rotated180, n)) {
        printf("2\n");
    } else if (compare(final, rotated270, n)) {
        printf("3\n");
    } else {
        printf("7\n");
    }
    
    return 0;
}