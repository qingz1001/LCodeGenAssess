#include <stdio.h>
#include <string.h>

#define MAXN 50005

char s[MAXN];
int n, m;

void update(int l, int r, char c) {
    for (int i = l; i <= r; i++) {
        if (s[i] == c) continue;
        s[i] = c;
    }
}

void query(int l, int r, char c) {
    int count = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == c) count++;
    }
    printf("%d\n", count);
}

void sort(int l, int r) {
    char temp[r - l + 2];
    strncpy(temp, s + l, r - l + 1);
    temp[r - l + 1] = '\0';
    qsort(temp, r - l + 1, sizeof(char), (int (*)(const void *, const void *))strcmp);
    strncpy(s + l, temp, r - l + 1);
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    for (int i = 0; i < m; i++) {
        int op, l, r;
        char c;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 1) {
            scanf(" %c", &c);
            query(l, r, c);
        } else if (op == 2) {
            scanf(" %c", &c);
            update(l, r, c);
        } else if (op == 3) {
            sort(l, r);
        }
    }

    return 0;
}