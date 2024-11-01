#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

int parent[MAX_N];
int rank[MAX_N];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    
    if (root_x != root_y) {
        if (rank[root_x] < rank[root_y]) {
            parent[root_x] = root_y;
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        } else {
            parent[root_y] = root_x;
            rank[root_x]++;
        }
    }
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
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