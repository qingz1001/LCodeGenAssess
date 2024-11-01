#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 100005
#define MAXM 200005
#define MAXQ 100005

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double h;
} Edge;

typedef struct {
    Edge e;
    int next;
} AdjacencyList;

Point points[MAXN];
Edge edges[MAXM];
AdjacencyList adjacencyList[MAXM];
int head[MAXN];
int n, m, q;
double queryPoints[MAXQ][4];

void addEdge(int u, int v, double h) {
    int index = m++;
    edges[index].u = u;
    edges[index].v = v;
    edges[index].h = h;
    adjacencyList[index].e = edges[index];
    adjacencyList[index].next = head[u];
    head[u] = index;
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double query(double ax, double ay, double bx, double by) {
    // TODO: Implement the query function to find the minimum edge weight that can be crossed
    return 0.0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        double h;
        scanf("%d %d %lf", &u, &v, &h);
        u--; v--;
        addEdge(u, v, h);
        addEdge(v, u, h);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%lf %lf %lf %lf", &queryPoints[i][0], &queryPoints[i][1], &queryPoints[i][2], &queryPoints[i][3]);
    }
    for (int i = 0; i < q; i++) {
        double result = query(queryPoints[i][0], queryPoints[i][1], queryPoints[i][2], queryPoints[i][3]);
        printf("%lf\n", result);
    }
    return 0;
}