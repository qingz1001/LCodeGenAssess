#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义结构体存储字符及其原始位置
typedef struct {
    char ch;
    int pos;
} CharInfo;

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    CharInfo *c = (CharInfo *)a;
    CharInfo *d = (CharInfo *)b;
    if (c->ch == d->ch) {
        return c->pos - d->pos;
    } else {
        return c->ch - d->ch;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // 读取换行符

    CharInfo arr[n];
    char s[n + 1];
    fgets(s, n + 1, stdin); // 读取字符串并包括末尾的换行符
    s[n] = '\0'; // 手动添加字符串结束符

    int p;
    scanf("%d", &p);

    // 填充结构体数组
    for (int i = 0; i < n; i++) {
        arr[i].ch = s[i];
        arr[i].pos = i;
    }

    // 排序
    qsort(arr, n, sizeof(CharInfo), compare);

    // 输出原字符串
    for (int i = 0; i < n; i++) {
        if (arr[i].pos == p - 1) {
            printf("%c", arr[i].ch);
            for (int j = 0; j < n; j++) {
                if (arr[i].pos == j) continue;
                printf("%c", arr[j].ch);
            }
            break;
        }
    }

    return 0;
}