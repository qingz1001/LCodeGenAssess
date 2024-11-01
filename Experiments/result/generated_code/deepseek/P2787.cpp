#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 50005

char s[MAXN];

int count_char(char *str, int x, int y, char k) {
    int count = 0;
    for (int i = x - 1; i < y; i++) {
        if (tolower(str[i]) == tolower(k)) {
            count++;
        }
    }
    return count;
}

void replace_char(char *str, int x, int y, char k) {
    for (int i = x - 1; i < y; i++) {
        str[i] = tolower(k);
    }
}

void sort_string(char *str, int x, int y) {
    int count[26] = {0};
    for (int i = x - 1; i < y; i++) {
        count[tolower(str[i]) - 'a']++;
    }
    int idx = x - 1;
    for (int i = 0; i < 26; i++) {
        while (count[i] > 0) {
            str[idx++] = 'a' + i;
            count[i]--;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    for (int i = 0; i < m; i++) {
        int op, x, y;
        char k;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %c", &x, &y, &k);
            printf("%d\n", count_char(s, x, y, k));
        } else if (op == 2) {
            scanf("%d %d %c", &x, &y, &k);
            replace_char(s, x, y, k);
        } else if (op == 3) {
            scanf("%d %d", &x, &y);
            sort_string(s, x, y);
        }
    }

    return 0;
}