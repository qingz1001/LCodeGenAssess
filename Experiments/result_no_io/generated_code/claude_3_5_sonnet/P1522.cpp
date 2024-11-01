#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_N 150
#define INF 1e9

int N;
double x[MAX_N], y[MAX_N];
int adj[MAX_N][MAX_N];
double dist[MAX_N][MAX_N];
double maxDist[MAX_N];
int comp[MAX_N];

double calcDist(int i, int j) {
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}

void floyd() {
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

void dfs(int u, int c) {
    comp[u] = c;
    for (int v = 0; v < N; v++)
        if (adj[u][v] && !comp[v])
            dfs(v, c);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%lf%lf", &x[i], &y[i]);
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            scanf("%d", &adj[i][j]);
            if (i == j) dist[i][j] = 0;
            else if (adj[i][j]) dist[i][j] = calcDist(i, j);
            else dist[i][j] = INF;
        }
    
    floyd();
    
    int compNum = 0;
    for (int i = 0; i < N; i++)
        if (!comp[i])
            dfs(i, ++compNum);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (dist[i][j] < INF && dist[i][j] > maxDist[i])
                maxDist[i] = dist[i][j];
    }
    
    double maxComp[MAX_N] = {0};
    for (int i = 0; i < N; i++)
        if (maxDist[i] > maxComp[comp[i]])
            maxComp[comp[i]] = maxDist[i];
    
    double ans = DBL_MAX;
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
            if (comp[i] != comp[j]) {
                double newDiam = fmax(maxComp[comp[i]], maxComp[comp[j]]);
                newDiam = fmax(newDiam, maxDist[i] + maxDist[j] + calcDist(i, j));
                if (newDiam < ans) ans = newDiam;
            }
    
    printf("%.6f\n", ans);
    return 0;
}