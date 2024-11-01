#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    char str1[20], str2[20];
    sprintf(str1, "%s%s", *(char**)a, *(char**)b);
    sprintf(str2, "%s%s", *(char**)b, *(char**)a);
    return strcmp(str2, str1);
}

int main() {
    int n;
    scanf("%d", &n);
    char *a[20];

    // 读取输入
    for (int i = 0; i < n; i++) {
        a[i] = (char*)malloc(20 * sizeof(char));
        scanf("%s", a[i]);
    }

    // 排序
    qsort(a, n, sizeof(char*), compare);

    // 输出结果
    for (int i = 0; i < n; i++) {
        printf("%s", a[i]);
        free(a[i]);
    }

    return 0;
}