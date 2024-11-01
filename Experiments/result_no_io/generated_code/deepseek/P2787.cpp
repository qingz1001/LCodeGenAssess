#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 50001

char mind[MAXN];

int count_char(int x, int y, char k) {
    int count = 0;
    for (int i = x; i <= y; i++) {
        if (tolower(mind[i]) == tolower(k)) {
            count++;
        }
    }
    return count;
}

void replace_char(int x, int y, char k) {
    for (int i = x; i <= y; i++) {
        mind[i] = tolower(k);
    }
}

void sort_chars(int x, int y) {
    int count[26] = {0};
    for (int i = x; i <= y; i++) {
        count[tolower(mind[i]) - 'a']++;
    }
    int idx = x;
    for (int i = 0; i < 26; i++) {
        while (count[i] > 0) {
            mind[idx++] = 'a' + i;
            count[i]--;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", mind);

    for (int i = 0; i < m; i++) {
        int op, x, y;
        char k;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %c", &x, &y, &k);
            printf("%d\n", count_char(x - 1, y - 1, k));
        } else if (op == 2) {
            scanf("%d %d %c", &x, &y, &k);
            replace_char(x - 1, y - 1, k);
        } else if (op == 3) {
            scanf("%d %d", &x, &y);
            sort_chars(x - 1, y - 1);
        }
    }

    return 0;
}