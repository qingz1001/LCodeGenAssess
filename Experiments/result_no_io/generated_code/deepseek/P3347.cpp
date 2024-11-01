#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXM 100

typedef struct {
    int a, b, c;
} Distillery;

typedef struct {
    int capacity;
} Storage;

int n, m;
Distillery distilleries[MAXN];
Storage storages[MAXM];
int connections[MAXN][MAXM];

int max_storage_capacity() {
    int total_capacity = 0;
    for (int j = 0; j < m; j++) {
        total_capacity += storages[j].capacity;
    }
    return total_capacity;
}

double calculate_cost(int distillery_index, double amount) {
    Distillery d = distilleries[distillery_index];
    return d.a * amount * amount + d.b * amount;
}

void solve() {
    int max_capacity = max_storage_capacity();
    printf("%d\n", max_capacity);

    // Initialize minimum cost to a large value
    double min_cost = INT_MAX;

    // Brute force approach to find the minimum cost
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (connections[i][j]) {
                double amount = (double)storages[j].capacity;
                if (amount > distilleries[i].c) {
                    amount = distilleries[i].c;
                }
                double cost = calculate_cost(i, amount);
                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
        }
    }

    // Simplify the cost to a/b form
    int a = (int)min_cost;
    int b = 1;
    printf("%d/%d\n", a, b);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &distilleries[i].a, &distilleries[i].b, &distilleries[i].c);
    }
    for (int j = 0; j < m; j++) {
        scanf("%d", &storages[j].capacity);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &connections[i][j]);
        }
    }

    solve();
    return 0;
}