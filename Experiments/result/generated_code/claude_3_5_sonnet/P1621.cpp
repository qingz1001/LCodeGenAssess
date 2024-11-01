#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100001

int parent[MAX_N];
int rank[MAX_N];

void make_set(int x) {
    parent[x] = x;
    rank[x] = 0;
}

int find_set(int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int px = find_set(x);
    int py = find_set(y);
    if (px == py) return;
    if (rank[px] < rank[py]) {
        parent[px] = py;
    } else if (rank[px] > rank[py]) {
        parent[py] = px;
    } else {
        parent[py] = px;
        rank[px]++;
    }
}

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool has_common_prime_factor(int a, int b, int p) {
    int g = gcd(a, b);
    if (g < p) return false;
    for (int i = p; i * i <= g; i++) {
        if (g % i == 0) return true;
    }
    return g >= p;
}

int main() {
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);

    for (int i = a; i <= b; i++) {
        make_set(i);
    }

    for (int i = a; i <= b; i++) {
        for (int j = i + 1; j <= b; j++) {
            if (has_common_prime_factor(i, j, p)) {
                union_sets(i, j);
            }
        }
    }

    int count = 0;
    for (int i = a; i <= b; i++) {
        if (find_set(i) == i) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}