#include <stdio.h>
#include <stdbool.h>

#define MAXN 10

void rotate90(char src[MAXN][MAXN], char dest[MAXN][MAXN], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[j][n - 1 - i] = src[i][j];
        }
    }
}

void reflect(char src[MAXN][MAXN], char dest[MAXN][MAXN], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][n - 1 - j] = src[i][j];
        }
    }
}

bool compare(char a[MAXN][MAXN], char b[MAXN][MAXN], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

int main() {
    int n;
    char initial[MAXN][MAXN], target[MAXN][MAXN];
    char temp[MAXN][MAXN], temp2[MAXN][MAXN];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", initial[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", target[i]);
    }

    // Check 90 degree rotation
    rotate90(initial, temp, n);
    if (compare(temp, target, n)) {
        printf("1\n");
        return 0;
    }

    // Check 180 degree rotation
    rotate90(temp, temp2, n);
    if (compare(temp2, target, n)) {
        printf("2\n");
        return 0;
    }

    // Check 270 degree rotation
    rotate90(temp2, temp, n);
    if (compare(temp, target, n)) {
        printf("3\n");
        return 0;
    }

    // Check reflection
    reflect(initial, temp, n);
    if (compare(temp, target, n)) {
        printf("4\n");
        return 0;
    }

    // Check combination (reflection + 90, 180, 270 degree rotation)
    rotate90(temp, temp2, n);
    if (compare(temp2, target, n)) {
        printf("5\n");
        return 0;
    }
    rotate90(temp2, temp, n);
    if (compare(temp, target, n)) {
        printf("5\n");
        return 0;
    }
    rotate90(temp, temp2, n);
    if (compare(temp2, target, n)) {
        printf("5\n");
        return 0;
    }

    // Check no change
    if (compare(initial, target, n)) {
        printf("6\n");
        return 0;
    }

    // Invalid transformation
    printf("7\n");
    return 0;
}