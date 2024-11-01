#include <stdio.h>
#include <stdlib.h>

#define MAXN 151

int parent[MAXN];
int size[MAXN];

void make_set(int x) {
    parent[x] = x;
    size[x] = 1;
}

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find_set(x);
    int rootY = find_set(y);
    if (rootX != rootY) {
        if (size[rootX] > size[rootY]) {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        } else {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
    }
}

int main() {
    int N, P;
    scanf("%d %d", &N, &P);

    for (int i = 1; i <= N; ++i)
        make_set(i);

    for (int i = 1; i < N; ++i) {
        int I, J;
        scanf("%d %d", &I, &J);
        union_sets(I, J);
    }

    int result = 0;
    for (int i = 1; i <= N; ++i) {
        if (find_set(i) == i && size[i] == P) {
            result++;
        }
    }

    printf("%d\n", result);

    return 0;
}