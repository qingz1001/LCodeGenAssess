#include <stdio.h>
#include <stdbool.h>

#define MAXN 100005

int parent[MAXN];
bool prime[MAXN];

void make_set(int x) {
    parent[x] = x;
}

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find_set(x)] = find_set(y);
}

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!prime[i]) {
            for (int j = i * 2; j <= n; j += i) {
                prime[j] = true;
            }
        }
    }
}

bool has_common_prime_factor(int x, int y, int p) {
    for (int i = 2; i <= x && i <= y; i++) {
        if (!prime[i])
            continue;
        if (x % i == 0 && y % i == 0 && i >= p) {
            return true;
        }
    }
    return false;
}

int main() {
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);

    sieve(b);

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
        if (parent[i] == i) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}