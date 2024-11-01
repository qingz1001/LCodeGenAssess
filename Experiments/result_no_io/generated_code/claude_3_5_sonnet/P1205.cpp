#include <stdio.h>
#include <string.h>

#define MAX_N 10

char original[MAX_N][MAX_N], transformed[MAX_N][MAX_N], temp[MAX_N][MAX_N];
int n;

void rotate90() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[j][n-1-i] = original[i][j];
    memcpy(original, temp, sizeof(original));
}

void reflect() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][n-1-j] = original[i][j];
    memcpy(original, temp, sizeof(original));
}

int compare() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (original[i][j] != transformed[i][j])
                return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", original[i]);
    for (int i = 0; i < n; i++)
        scanf("%s", transformed[i]);

    // 90 degree rotation
    rotate90();
    if (compare()) {
        printf("1\n");
        return 0;
    }

    // 180 degree rotation
    rotate90();
    if (compare()) {
        printf("2\n");
        return 0;
    }

    // 270 degree rotation
    rotate90();
    if (compare()) {
        printf("3\n");
        return 0;
    }

    // Reflection
    rotate90(); // Back to original
    reflect();
    if (compare()) {
        printf("4\n");
        return 0;
    }

    // Combination
    for (int i = 0; i < 3; i++) {
        rotate90();
        if (compare()) {
            printf("5\n");
            return 0;
        }
    }

    // No change
    rotate90(); // Back to original
    if (compare()) {
        printf("6\n");
        return 0;
    }

    // Invalid transformation
    printf("7\n");
    return 0;
}