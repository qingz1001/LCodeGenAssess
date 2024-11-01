#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 301
#define MAX_NEIGHBORS 600

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int parents1[MAX] = {0};
    int parents2[MAX] = {0};
    int neighbors[MAX][MAX_NEIGHBORS];
    int neighbor_count[MAX];
    memset(neighbor_count, 0, sizeof(neighbor_count));
    int indegree[MAX] = {0};
    for(int i=0;i<k;i++){
        int c, a, b;
        scanf("%d %d %d", &c, &a, &b);
        parents1[c] = a;
        parents2[c] = b;
        neighbors[a][neighbor_count[a]++] = c;
        neighbors[b][neighbor_count[b]++] = c;
        indegree[c]++;
        indegree[c]++;
    }
    // Topological sort
    int topo[MAX];
    int topo_size =0;
    int queue[MAX];
    int front=0, rear=0;
    for(int i=1;i<=n;i++) if(indegree[i]==0) queue[rear++] = i;
    while(front < rear){
        int u = queue[front++];
        topo[topo_size++] = u;
        for(int i=0;i<neighbor_count[u];i++){
            int v = neighbors[u][i];
            indegree[v]--;
            if(indegree[v]==0){
                queue[rear++] = v;
            }
        }
    }
    // Initialize S
    double S[MAX][MAX];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i == j) S[i][j] = 1.0;
            else S[i][j] = 0.0;
        }
    }
    // Compute S
    for(int i=0;i<topo_size;i++){
        int X = topo[i];
        if(parents1[X]==0 && parents2[X]==0) continue;
        for(int j=0; j<topo_size; j++){
            int Y = topo[j];
            if(Y > X) continue;
            if(parents1[Y]==0 && parents2[Y]==0 && Y != X){
                // S[X][Y] remains 0
                continue;
            }
            if(parents1[X] && parents2[X] && parents1[Y] && parents2[Y]){
                int a = parents1[X];
                int b = parents2[X];
                int c = parents1[Y];
                int d = parents2[Y];
                S[X][Y] = 0.25*(S[a][c] + S[a][d] + S[b][c] + S[b][d]);
                // Symmetry
                S[Y][X] = S[X][Y];
            }
        }
    }
    int m;
    scanf("%d", &m);
    for(int i=0;i<m;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        double val = S[x][y] * 100.0;
        char temp[50];
        sprintf(temp, "%.10lf", val);
        // Remove trailing zeros
        int len = strlen(temp);
        while(len >0 && temp[len-1]=='0') len--;
        if(len >0 && temp[len-1]=='.') len--;
        temp[len] = '\0';
        printf("%s%%\n", temp);
    }
    return 0;
}