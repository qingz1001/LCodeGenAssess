#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 101

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int N;
    scanf("%d", &N);

    char **words = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        words[i] = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
        scanf("%s", words[i]);
    }

    char T[MAX_WORD_LENGTH];
    scanf("%s", T);

    // 对单词数组进行排序
    qsort(words, N, sizeof(char *), compare);

    // 输出以T为前缀的单词
    for (int i = 0; i < N; i++) {
        if (strncmp(words[i], T, strlen(T)) == 0) {
            printf("%s\n", words[i]);
        }
    }

    // 释放内存
    for (int i = 0; i < N; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}