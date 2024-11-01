#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 32
#define MAX_M 1000

int n, m;
int s[MAX_M], e[MAX_M], c[MAX_M];

int min_loss = INT_MAX;
int min_trucks = INT_MAX;

void dfs(int pos, int current_loss, int current_trucks, int visited) {
    if (pos == n - 1) {
        if (current_loss < min_loss || (current_loss == min_loss && current_trucks < min_trucks)) {
            min_loss = current_loss;
            min_trucks = current_trucks;
        }
        return;
    }

    for (int i = 0; i < m; i++) {
        if ((visited & (1 << i)) == 0 && pos + 1 == s[i]) {
            dfs(e[i], current_loss + c[i], current_trucks + 1, visited | (1 << i));
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &s[i], &e[i], &c[i]);
    }

    dfs(0, 0, 0, 0);

    printf("%d %d\n", min_loss, min_trucks);
    return 0;
}