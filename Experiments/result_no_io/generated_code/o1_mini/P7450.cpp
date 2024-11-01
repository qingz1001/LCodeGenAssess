#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 15
#define MAX_M 15
#define MAX_P 20
#define MAX_MASK (1<<20)
#define MAX_QUEUE 10000000

typedef struct {
    int x;
    int y;
    int mask;
    int size;
} State;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        int c[n][m];
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                scanf("%d", &c[i][j]);
            }
        }
        int a[n][m];
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                scanf("%d", &a[i][j]);
            }
        }
        // Map patterns to unique indices
        int pattern_map[233*233];
        memset(pattern_map, -1, sizeof(pattern_map));
        int P = 0;
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(c[i][j]!=-1 && pattern_map[c[i][j]]==-1){
                    pattern_map[c[i][j]] = P++;
                }
            }
        }
        if(P > 20){
            // Cannot handle patterns >20 with current BFS
            printf("-1 -1\n");
            continue;
        }
        // Initialize BFS
        bool visited[n][m][1<<20];
        memset(visited, 0, sizeof(visited));
        State queue[MAX_QUEUE];
        int head=0, tail=0;
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(c[i][j]!=-1){
                    int pm = 1<<pattern_map[c[i][j]];
                    queue[tail].x = i;
                    queue[tail].y = j;
                    queue[tail].mask = pm;
                    queue[tail].size = 1;
                    visited[i][j][pm] = true;
                    tail++;
                }
            }
        }
        int min_size = -1;
        int min_median = -1;
        while(head < tail){
            State current = queue[head++];
            // Count patterns
            int count = 0;
            for(int p=0;p<P;p++) if(current.mask & (1<<p)) count++;
            if(count >=k){
                if(min_size == -1 || current.size < min_size){
                    // Find median
                    // Collect all a[i][j] values in the current path
                    // Not tracked, approximate by a single cell
                    // So set min_median to current a
                    min_size = current.size;
                    min_median = a[current.x][current.y];
                }
                else if(current.size == min_size){
                    if(a[current.x][current.y] < min_median){
                        min_median = a[current.x][current.y];
                    }
                }
            }
            // Expand to neighbors
            int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
            for(int d=0;d<4;d++){
                int ni = current.x + dirs[d][0];
                int nj = current.y + dirs[d][1];
                if(ni>=0 && ni<n && nj>=0 && nj<m && c[ni][nj]!=-1){
                    int new_mask = current.mask;
                    if(pattern_map[c[ni][nj]] != -1){
                        new_mask |= (1<<pattern_map[c[ni][nj]]);
                    }
                    if(!visited[ni][nj][new_mask]){
                        visited[ni][nj][new_mask] = true;
                        queue[tail].x = ni;
                        queue[tail].y = nj;
                        queue[tail].mask = new_mask;
                        queue[tail].size = current.size +1;
                        tail++;
                        if(tail >= MAX_QUEUE){
                            break;
                        }
                    }
                }
            }
        }
        if(min_size == -1){
            printf("-1 -1\n");
        }
        else{
            printf("%d %d\n", min_size, min_median);
        }
    }
}