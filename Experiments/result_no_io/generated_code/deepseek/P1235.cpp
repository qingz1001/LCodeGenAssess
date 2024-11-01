#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 300

typedef struct {
    int parent1;
    int parent2;
} Monster;

Monster monsters[MAXN + 1];

double similarity(int x, int y) {
    if (x == y) return 1.0;
    if (monsters[x].parent1 == 0 || monsters[y].parent1 == 0) return 0.0;

    double sim1 = similarity(monsters[x].parent1, monsters[y].parent1) + similarity(monsters[x].parent1, monsters[y].parent2);
    double sim2 = similarity(monsters[x].parent2, monsters[y].parent1) + similarity(monsters[x].parent2, monsters[y].parent2);

    return (sim1 + sim2) / 4.0;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        monsters[i].parent1 = 0;
        monsters[i].parent2 = 0;
    }

    for (int i = 0; i < k; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        monsters[a].parent1 = b;
        monsters[a].parent2 = c;
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        double sim = similarity(x, y) * 100.0;
        printf("%.1f%%\n", sim);
    }

    return 0;
}