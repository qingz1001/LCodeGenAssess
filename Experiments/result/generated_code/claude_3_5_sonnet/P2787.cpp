#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_N 50005

char str[MAX_N];
int n, m;

void query(int x, int y, char k) {
    int count = 0;
    for (int i = x; i <= y; i++) {
        if (tolower(str[i]) == tolower(k)) {
            count++;
        }
    }
    printf("%d\n", count);
}

void replace(int x, int y, char k) {
    for (int i = x; i <= y; i++) {
        str[i] = k;
    }
}

void sort(int x, int y) {
    int count[26] = {0};
    for (int i = x; i <= y; i++) {
        count[tolower(str[i]) - 'a']++;
    }
    int idx = x;
    for (int i = 0; i < 26; i++) {
        while (count[i]--) {
            str[idx++] = 'a' + i;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", str+1);

    int op, x, y;
    char k;
    for (int i = 0; i < m; i++) {
        scanf("%d", &op);
        if (op == 1 || op == 2) {
            scanf("%d %d %c", &x, &y, &k);
            if (op == 1) query(x, y, k);
            else replace(x, y, k);
        } else {
            scanf("%d %d", &x, &y);
            sort(x, y);
        }
    }

    return 0;
}