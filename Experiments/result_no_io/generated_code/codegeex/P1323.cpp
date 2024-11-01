#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// 删除m个数位上的数字，使得剩下的数字最大
void deleteDigits(char *str, int m) {
    int len = strlen(str);
    int stack[len + 1];
    int top = 0;

    for (int i = 0; i < len; i++) {
        while (top > 0 && stack[top - 1] > str[i] && m > 0) {
            top--;
            m--;
        }
        stack[top++] = str[i];
    }

    while (m > 0) {
        top--;
        m--;
    }

    int index = 0;
    for (int i = 0; i < top; i++) {
        str[index++] = stack[i];
    }
    str[index] = '\0';
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    // 初始化集合
    int *set = (int *)malloc(sizeof(int) * 30001);
    set[0] = 1;
    int count = 1;

    for (int i = 0; i < k; i++) {
        set[count++] = 2 * set[i] + 1;
        set[count++] = 4 * set[i] + 5;
    }

    // 对集合进行排序
    qsort(set, count, sizeof(int), compare);

    // 将最小的k个元素组合成一个多位数
    char number[100001];
    number[0] = '\0';
    for (int i = 0; i < k; i++) {
        sprintf(number, "%s%d", number, set[i]);
    }

    // 输出删除前的数字
    printf("%s\n", number);

    // 删除m个数位上的数字
    deleteDigits(number, m);

    // 输出删除后的数字
    printf("%s\n", number);

    free(set);
    return 0;
}