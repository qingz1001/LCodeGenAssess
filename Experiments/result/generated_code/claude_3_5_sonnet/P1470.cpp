#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ELEMENTS 200
#define MAX_ELEMENT_LENGTH 10
#define MAX_SEQUENCE_LENGTH 200000

char elements[MAX_ELEMENTS][MAX_ELEMENT_LENGTH + 1];
int num_elements = 0;
char sequence[MAX_SEQUENCE_LENGTH + 1];
bool dp[MAX_SEQUENCE_LENGTH + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    // 读取元素集合
    while (1) {
        char element[MAX_ELEMENT_LENGTH + 1];
        scanf("%s", element);
        if (element[0] == '.') break;
        strcpy(elements[num_elements++], element);
    }

    // 读取序列
    char buffer[77];
    int seq_len = 0;
    while (scanf("%76s", buffer) == 1) {
        strcat(sequence, buffer);
    }
    seq_len = strlen(sequence);

    // 动态规划
    dp[0] = true;
    int max_prefix = 0;
    for (int i = 1; i <= seq_len; i++) {
        for (int j = 0; j < num_elements; j++) {
            int len = strlen(elements[j]);
            if (i >= len && strncmp(sequence + i - len, elements[j], len) == 0 && dp[i - len]) {
                dp[i] = true;
                max_prefix = i;
                break;
            }
        }
    }

    // 输出结果
    printf("%d\n", max_prefix);

    return 0;
}