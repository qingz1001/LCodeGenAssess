#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXM 20000
#define MAXN 20000
#define MAXEDGES 2000000
#define INF 1000000000

struct Edge {
    int to;
    int next;
} edges[MAXEDGES];

int head_list[MAXM + 1];
int edge_cnt_global;

int pairU_global[MAXM +1];
int pairV_global[MAXN +1];
int dist_global[MAXM +1];

int queue_global[MAXM +1];

int m_global, n_global;

int bfs() {
    int front = 0, rear = 0;
    for(int u =1; u <= m_global; u++) {
        if(pairU_global[u]==0){
            dist_global[u]=0;
            queue_global[rear++] = u;
        }
        else{
            dist_global[u]=INF;
        }
    }
    dist_global[0] = INF;
    while(front < rear){
        int u = queue_global[front++];
        if(u !=0){
            for(int e = head_list[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                if(pairV_global[v]==0){
                    if(dist_global[0] == INF){
                        dist_global[0] = dist_global[u] +1;
                    }
                }
                else{
                    if(dist_global[pairV_global[v]] == INF){
                        dist_global[pairV_global[v]] = dist_global[u] +1;
                        queue_global[rear++] = pairV_global[v];
                    }
                }
            }
        }
    }
    return dist_global[0]!=INF;
}

int dfs(int u){
    if(u !=0){
        for(int e = head_list[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            if(pairV_global[v]==0 || (dist_global[pairV_global[v]] == dist_global[u] +1 && dfs(pairV_global[v]))){
                pairU_global[u] = v;
                pairV_global[v] = u;
                return 1;
            }
        }
        dist_global[u] = INF;
        return 0;
    }
    return 1;
}

int hopcroft_karp(){
    memset(pairU_global, 0, sizeof(int)*(m_global+1));
    memset(pairV_global, 0, sizeof(int)*(n_global+1));
    int matching =0;
    while(bfs()){
        for(int u=1; u<=m_global; u++) {
            if(pairU_global[u]==0){
                if(dfs(u)){
                    matching++;
                }
            }
        }
    }
    return matching;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &m_global, &n_global);
        memset(head_list, -1, sizeof(int)*(m_global+1));
        edge_cnt_global =0;
        for(int i=1;i<=m_global;i++){
            int k;
            scanf("%d", &k);
            for(int j=0; j<k; j++){
                int p;
                scanf("%d", &p);
                edges[edge_cnt_global].to = p;
                edges[edge_cnt_global].next = head_list[i];
                head_list[i] = edge_cnt_global++;
            }
        }
        int match = hopcroft_karp();
        if(match >= m_global){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}