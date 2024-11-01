#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005

int n;
int a[MAX_N], b[MAX_N];
int parent[MAX_N * 2];
int size[MAX_N * 2];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) {
        int temp = x;
        x = y;
        y = temp;
    }
    parent[y] = x;
    size[x] += size[y];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }

    for (int i = 1; i <= 2 * n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        unite(a[i], b[i]);
    }

    int count = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (find(i) == i) {
            count++;
        }
    }

    printf("%d\n", count - 1);

    return 0;
}