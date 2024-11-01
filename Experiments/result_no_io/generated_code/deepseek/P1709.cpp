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

    // 将字符串复制一份拼接在后面
    memcpy(S + N, S, N);

    // 使用数组存储所有可能的字符串
    char *strings[N];
    for (int i = 0; i < N; i++) {
        strings[i] = S + i;
    }

    // 对所有字符串进行排序
    qsort(strings, N, sizeof(char *), compare);

    // 找到第一个字符串的第一个字符在原字符串中的位置
    for (int i = 0; i < N; i++) {
        if (strings[0][0] == S[i]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}