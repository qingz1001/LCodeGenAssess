#include <stdio.h>
#include <string.h>

int n;
char original[11][11], transformed[11][11];

void rotate90() {
    char rotated[11][11];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotated[j][n - 1 - i] = original[i][j];
        }
    }
    memcpy(original, rotated, sizeof(rotated));
}

void reflect() {
    char reflected[11][11];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            reflected[i][n - 1 - j] = original[i][j];
        }
    }
    memcpy(original, reflected, sizeof(reflected));
}

int compare() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (original[i][j] != transformed[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", original[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", transformed[i]);
    }

    // 旋转90度
    rotate90();
    if (compare()) {
        printf("1\n");
        return 0;
    }

    // 旋转180度
    rotate90();
    if (compare()) {
        printf("2\n");
        return 0;
    }

    // 旋转270度
    rotate90();
    if (compare()) {
        printf("3\n");
        return 0;
    }

    // 反射
    rotate90();
    reflect();
    if (compare()) {
        printf("4\n");
        return 0;
    }

    // 组合转换
    rotate90();
    if (compare()) {
        printf("5\n");
        return 0;
    }
    rotate90();
    if (compare()) {
        printf("5\n");
        return 0;
    }
    rotate90();
    if (compare()) {
        printf("5\n");
        return 0;
    }

    // 不改变
    rotate90();
    if (compare()) {
        printf("6\n");
        return 0;
    }

    // 无效转换
    printf("7\n");
    return 0;
}