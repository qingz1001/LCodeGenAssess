#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 300

typedef struct {
    int parent1;
    int parent2;
} Monster;

Monster monsters[MAXN + 1];

void findParents(int x, int *p1, int *p2) {
    if (monsters[x].parent1 == 0 && monsters[x].parent2 == 0) {
        *p1 = *p2 = x;
    } else {
        *p1 = monsters[x].parent1;
        *p2 = monsters[x].parent2;
    }
}

double calculateSimilarity(int x, int y) {
    if (x == y) return 1.0;

    int px1, px2, py1, py2;
    findParents(x, &px1, &px2);
    findParents(y, &py1, &py2);

    if ((px1 == py1 && px2 == py2) || (px1 == py2 && px2 == py1)) return 1.0;

    if (px1 == py1 || px1 == py2 || px2 == py1 || px2 == py2) return 0.5;

    int gx1, gx2, gy1, gy2;
    findParents(px1, &gx1, &gx2);
    findParents(px2, &gx1, &gx2);
    findParents(py1, &gy1, &gy2);
    findParents(py2, &gy1, &gy2);

    if ((gx1 == gy1 && gx2 == gy2) || (gx1 == gy2 && gx2 == gy1)) return 0.5;

    if (gx1 == gy1 || gx1 == gy2 || gx2 == gy1 || gx2 == gy2) return 0.25;

    return 0.125;
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
        double similarity = calculateSimilarity(x, y) * 100;
        printf("%.0f%%\n", similarity);
    }

    return 0;
}