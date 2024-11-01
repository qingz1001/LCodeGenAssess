#include <stdio.h>
#include <string.h>

#define MAXN 50005

char s[MAXN];
int arr[MAXN];

void update(int l, int r, char c) {
    for (int i = l; i <= r; i++) {
        if (s[i] == c) arr[i]++;
    }
}

void assign(int l, int r, char c) {
    for (int i = l; i <= r; i++) {
        s[i] = c;
        arr[i] = 0;
        if (s[i] == c) arr[i]++;
    }
}

void sort_range(int l, int r) {
    for (int i = l; i <= r; i++) {
        arr[i] = 0;
    }
    for (int i = l; i <= r; i++) {
        arr[i] = s[i];
    }
    qsort(arr + l, r - l + 1, sizeof(int), (int (*)(const void *, const void *))strcmp);
    for (int i = l; i <= r; i++) {
        s[i] = arr[i];
    }
}

int query(int l, int r, char c) {
    int count = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == c) count++;
    }
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    while (m--) {
        int type, x, y;
        char c;
        scanf("%d %d %d", &type, &x, &y);
        if (type == 1) {
            scanf(" %c", &c);
            printf("%d\n", query(x, y, c));
        } else if (type == 2) {
            scanf(" %c", &c);
            assign(x, y, c);
        } else if (type == 3) {
            sort_range(x, y);
        }
    }

    return 0;
}