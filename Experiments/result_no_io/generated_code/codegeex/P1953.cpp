#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char input[20];
    char output[20];
} FileNames;

int main() {
    int n, flag;
    char first[20], ext[10];
    FileNames files[100000];
    int startNum;
    char *dot;

    // 读取输入
    scanf("%s", first);
    if (first[0] >= '0' && first[0] <= '9') {
        flag = atoi(first);
        startNum = flag;
    } else {
        dot = strrchr(first, '.');
        if (dot) {
            strcpy(ext, dot + 1);
            *dot = '\0';
        } else {
            strcpy(ext, "");
        }
        flag = 0;
        startNum = 0;
    }

    // 读取文件名
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s %s", files[i].input, files[i].output);
    }

    // 生成新文件名
    for (int i = 0; i < n; i++) {
        if (flag) {
            printf("data%d %s\n", i + startNum, files[i].output);
        } else {
            char *dotInput = strrchr(files[i].input, '.');
            char *dotOutput = strrchr(files[i].output, '.');
            if (dotInput) {
                *dotInput = '\0';
            }
            if (dotOutput) {
                *dotOutput = '\0';
            }
            printf("%s %s\n", first, files[i].output);
        }
    }

    return 0;
}