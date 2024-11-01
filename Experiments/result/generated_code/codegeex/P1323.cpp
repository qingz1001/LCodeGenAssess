#include <stdio.h>
#include <stdlib.h>

// 删除数字函数
void deleteDigits(char *number, int m) {
    int len = strlen(number);
    int i, j;
    for (i = 0, j = 0; i < len && j < m; i++) {
        while (j < m && number[i] == '0') {
            i++;
        }
        if (i == len) {
            break;
        }
        number[j++] = number[i];
    }
    while (j < len) {
        number[j++] = '0';
    }
    number[j] = '\0';
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    // 生成最小的 k 个元素
    char number[100001];
    number[0] = '1';
    number[1] = '\0';
    int len = 1;
    for (int i = 0; i < k; i++) {
        char temp[100001];
        sprintf(temp, "%d", 2 * atoi(number) + 1);
        strcat(number, temp);
        sprintf(temp, "%d", 4 * atoi(number + len) + 5);
        strcat(number, temp);
        len = strlen(number);
    }

    // 输出删除前的数字
    printf("%s\n", number);

    // 删除 m 个数字
    deleteDigits(number, m);

    // 输出删除后的数字
    printf("%s\n", number);

    return 0;
}