#include <stdio.h>
#include <string.h>

#define N 10

char original[N][N];
char target[N][N];

void rotate90(char result[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[j][N - 1 - i] = original[i][j];
        }
    }
}

void rotate180(char result[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[N - 1 - i][N - 1 - j] = original[i][j];
        }
    }
}

void rotate270(char result[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[N - 1 - j][i] = original[i][j];
        }
    }
}

void flipHorizontal(char result[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][N - 1 - j] = original[i][j];
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", original[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%s", target[i]);
    }

    char temp[N][N];
    memcpy(temp, original, sizeof(original));

    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("1\n");
        return 0;
    }

    rotate90(temp);
    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("2\n");
        return 0;
    }

    rotate180(temp);
    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("3\n");
        return 0;
    }

    rotate270(temp);
    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("4\n");
        return 0;
    }

    flipHorizontal(temp);
    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("5\n");
        return 0;
    }

    rotate90(temp);
    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("6\n");
        return 0;
    }

    rotate180(temp);
    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("7\n");
        return 0;
    }

    rotate270(temp);
    if (memcmp(temp, target, sizeof(target)) == 0) {
        printf("7\n");
        return 0;
    }

    printf("0\n");
    return 0;
}