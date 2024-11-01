#include <stdio.h>
#include <stdbool.h>

#define MAXN 100005

int parent[MAXN];
int rank[MAXN];

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

bool hasCommonPrimeFactor(int a, int b, int p) {
    for (int i = 2; i * i <= a && i * i <= b; ++i) {
        if (a % i == 0 || b % i == 0) {
            while (a % i == 0) a /= i;
            while (b % i == 0) b /= i;
            if (i >= p) return true;
        }
    }
    return false;
}

int main() {
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);

    init(b + 1);

    for (int i = a; i <= b; ++i) {
        for (int j = i + 1; j <= b; ++j) {
            if (hasCommonPrimeFactor(i, j, p)) {
                unionSets(i, j);
            }
        }
    }

    int count = 0;
    for (int i = a; i <= b; ++i) {
        if (find(i) == i) count++;
    }

    printf("%d\n", count);
    return 0;
}