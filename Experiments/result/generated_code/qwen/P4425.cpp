#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, p;
int T[MAXN];
int LastAns = 0;

void update(int x, int y) {
    if (p == 0) {
        T[x] = y;
    } else {
        x ^= LastAns;
        y ^= LastAns;
        T[x] = y;
    }
}

int find(int s0) {
    int visited[MAXN] = {0};
    int current = s0;
    int count = 0;

    while (!visited[current]) {
        visited[current] = 1;
        current = (current + 1) % n;
        count++;
    }

    return count;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    for (int i = 0; i < n; i++) {
        scanf("%d", &T[i]);
    }

    // Initial answer
    for (int i = 0; i < n; i++) {
        if (T[i] != -1) {
            LastAns += find(i);
            break;
        }
    }

    printf("%d\n", LastAns);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        update(x, y);

        // Recalculate the answer after each update
        LastAns = 0;
        for (int j = 0; j < n; j++) {
            if (T[j] != -1) {
                LastAns += find(j);
                break;
            }
        }

        printf("%d\n", LastAns);
    }

    return 0;
}