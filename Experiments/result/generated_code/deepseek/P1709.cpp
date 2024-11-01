#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 5000005

char S[MAXN * 2];

int compare(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // 读取换行符

    int len = 0;
    while (len < N) {
        scanf("%72s", S + len);
        len += strlen(S + len);
    }

    // 复制字符串S到S的后半部分，形成一个长度为2N的字符串
    memcpy(S + N, S, N);

    // 找到字典序最小的字符串的起始位置
    int min_pos = 0;
    for (int i = 1; i < N; i++) {
        if (strcmp(S + i, S + min_pos) < 0) {
            min_pos = i;
        }
    }

    printf("%d\n", min_pos);

    return 0;
}