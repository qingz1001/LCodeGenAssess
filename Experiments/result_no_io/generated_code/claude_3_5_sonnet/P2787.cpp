#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 50005

char s[MAXN];
int n, m;

void count_occurrences(int x, int y, char k) {
    int count = 0;
    for (int i = x; i <= y; i++) {
        if (tolower(s[i]) == tolower(k)) {
            count++;
        }
    }
    printf("%d\n", count);
}

void replace_substring(int x, int y, char k) {
    for (int i = x; i <= y; i++) {
        s[i] = k;
    }
}

void sort_substring(int x, int y) {
    int len = y - x + 1;
    char temp[MAXN];
    strncpy(temp, s + x, len);
    temp[len] = '\0';
    
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (tolower(temp[j]) > tolower(temp[j+1])) {
                char t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }
        }
    }
    
    strncpy(s + x, temp, len);
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    for (int i = 0; i < m; i++) {
        int op, x, y;
        char k;
        scanf("%d %d %d", &op, &x, &y);
        x--; y--;  // 转换为0-based索引
        
        if (op == 1 || op == 2) {
            scanf(" %c", &k);
        }
        
        switch(op) {
            case 1:
                count_occurrences(x, y, k);
                break;
            case 2:
                replace_substring(x, y, k);
                break;
            case 3:
                sort_substring(x, y);
                break;
        }
    }

    return 0;
}