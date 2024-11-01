#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int parent[MAXN];
int rank[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
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

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);

    for (int i = a; i <= b; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = a; i <= b; i++) {
        for (int j = i + 1; j <= b; j++) {
            if (gcd(i, j) >= p) {
                union_sets(i, j);
            }
        }
    }

    int count = 0;
    for (int i = a; i <= b; i++) {
        if (parent[i] == i) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}