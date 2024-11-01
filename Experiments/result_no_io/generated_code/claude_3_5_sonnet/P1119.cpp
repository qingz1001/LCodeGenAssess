#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 201
#define MAX_M 20100
#define INF INT_MAX

int N, M, Q;
int t[MAX_N];
int dist[MAX_N][MAX_N];
int rebuild[MAX_N];

void floyd(int day) {
    int i, j, k;
    for (k = 0; k < N; k++) {
        if (rebuild[k] > day) continue;
        for (i = 0; i < N; i++) {
            if (rebuild[i] > day) continue;
            for (j = 0; j < N; j++) {
                if (rebuild[j] > day) continue;
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int i, j, w, x, y, t, last_day = -1;
    scanf("%d %d", &N, &M);
    
    for (i = 0; i < N; i++) {
        scanf("%d", &rebuild[i]);
    }
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }
    
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &x, &y, &w);
        dist[x][y] = dist[y][x] = w;
    }
    
    scanf("%d", &Q);
    
    while (Q--) {
        scanf("%d %d %d", &x, &y, &t);
        
        if (t > last_day) {
            floyd(t);
            last_day = t;
        }
        
        if (rebuild[x] > t || rebuild[y] > t || dist[x][y] == INF) {
            printf("-1\n");
        } else {
            printf("%d\n", dist[x][y]);
        }
    }
    
    return 0;
}