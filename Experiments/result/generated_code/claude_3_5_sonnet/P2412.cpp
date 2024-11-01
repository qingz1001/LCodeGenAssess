#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_N 100005
#define MAX_LEN 16

char words[MAX_N][MAX_LEN];
int N, M;

int compare(const char *a, const char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    for (int i = 0; i < len_a && i < len_b; i++) {
        char ca = tolower(a[i]), cb = tolower(b[i]);
        if (ca != cb) return ca - cb;
    }
    return len_a - len_b;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }

    int x, y;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &x, &y);
        x--; y--;  // 转换为0-based索引
        int max_index = y;
        for (int j = y - 1; j >= x; j--) {
            if (compare(words[j], words[max_index]) >= 0) {
                max_index = j;
            }
        }
        printf("%s\n", words[max_index]);
    }

    return 0;
}