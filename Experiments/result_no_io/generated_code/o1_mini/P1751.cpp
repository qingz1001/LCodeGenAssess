#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5001
#define MAXK 1001
#define MAXH 501

typedef struct Node {
    int adj[20];
    int adj_cnt;
} Node;

typedef struct Worm {
    int id;
    int pos;
    int cnt;
} Worm;

Node tree[MAXN];
int parent[MAXN];
int depth_arr[MAXN];
int k, h;
Worm worms[MAXK];
int food[MAXH];
int n;

// BFS to compute parent and depth
void bfs(int root) {
    int queue[MAXN];
    int front = 0, rear = 0;
    memset(parent, -1, sizeof(parent));
    memset(depth_arr, 0, sizeof(depth_arr));
    queue[rear++] = root;
    parent[root] = 0;
    depth_arr[root] = 0;
    while (front < rear) {
        int u = queue[front++];
        for(int i=0;i<tree[u].adj_cnt;i++){
            int v = tree[u].adj[i];
            if(parent[v]==-1){
                parent[v]=u;
                depth_arr[v]=depth_arr[u]+1;
                queue[rear++]=v;
            }
        }
    }
}

// Get path from u to v
int path[MAXN];
int get_path(int u, int v, int *plen){
    int path_u[MAXN], path_v[MAXN];
    int lenu=0, lenv=0;
    while(u != v){
        if(depth_arr[u] > depth_arr[v]){
            path_u[lenu++]=u;
            u = parent[u];
        }
        else{
            path_v[lenv++]=v;
            v = parent[v];
        }
    }
    for(int i=0;i<lenu;i++) path[i]=path_u[i];
    for(int i=lenv-1;i>=0;i--) path[lenu++]=path_v[i];
    *plen = lenu;
    return 0;
}

int main(){
    // Input
    scanf("%d", &n);
    for(int i=1;i<n;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        tree[A].adj[tree[A].adj_cnt++] = B;
        tree[B].adj[tree[B].adj_cnt++] = A;
    }
    bfs(1); // assuming 1 is root

    scanf("%d", &k);
    for(int i=1;i<=k;i++){
        scanf("%d", &worms[i].pos);
        worms[i].id = i;
        worms[i].cnt = 0;
    }
    scanf("%d", &h);
    for(int i=0;i<h;i++) scanf("%d", &food[i]);

    for(int f=0; f<h; f++){
        int target = food[f];
        // For each worm, find path to target
        int worm_path_len[MAXK];
        int *worm_path[MAXK];
        for(int i=1;i<=k;i++){
            worm_path[i] = path; // reuse the path array
            get_path(worms[i].pos, target, &worm_path_len[i]);
        }
        // Determine arrival times
        // Map of node and time to worm
        // To handle conflicts, track the earliest worm to reach each node at each time
        // Since time <= n, use arrays
        int occupied[MAXN];
        memset(occupied, 0, sizeof(occupied));
        int first_arrive = -1;
        int eater = -1;
        for(int t=0; t<n; t++){
            for(int i=1;i<=k;i++){
                if(t < worm_path_len[i]){
                    int u = path[t];
                    if(occupied[u] == 0){
                        occupied[u] = i;
                        if(u == target && (first_arrive == -1 || t < first_arrive || (t == first_arrive && i < eater))){
                            first_arrive = t;
                            eater = i;
                        }
                    }
                }
            }
            if(eater != -1 && t == first_arrive){
                break;
            }
        }
        if(eater != -1){
            worms[eater].cnt++;
            worms[eater].pos = target;
        }
        // Update positions
        for(int i=1;i<=k;i++){
            if(i == eater) continue;
            if(worm_path_len[i] <= first_arrive){
                worms[i].pos = target;
                continue;
            }
            if(first_arrive < worm_path_len[i]){
                worms[i].pos = path[first_arrive];
            }
        }
    }
    // Output
    for(int i=1;i<=k;i++) printf("%d %d\n", worms[i].pos, worms[i].cnt);
    return 0;
}