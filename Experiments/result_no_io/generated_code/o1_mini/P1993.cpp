#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5001
#define MAXM 20000

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
Edge edges_pool[MAXM];
int pool_ptr = 0;

void add_edge(int from, int to, int weight) {
    if(pool_ptr >= MAXM) return;
    edges_pool[pool_ptr].to = to;
    edges_pool[pool_ptr].weight = weight;
    edges_pool[pool_ptr].next = adj[from];
    adj[from] = &edges_pool[pool_ptr++];
}

long long dist_val[MAXN];
int in_queue_flag[MAXN];
int counts[MAXN];
int queue_[MAXN * 2];
int front = 0, rear = 0;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    memset(adj, 0, sizeof(adj));
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        if(type ==1){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            add_edge(a, b, -c);
        }
        else if(type ==2){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            add_edge(b, a, c);
        }
        else if(type ==3){
            int a, b;
            scanf("%d %d", &a, &b);
            add_edge(a, b, 0);
            add_edge(b, a, 0);
        }
    }
    for(int i=1;i<=n;i++){
        add_edge(0, i, 0);
    }
    for(int i=0;i<=n;i++) dist_val[i]=0;
    memset(in_queue_flag, 0, sizeof(in_queue_flag));
    memset(counts, 0, sizeof(counts));
    // Initialize queue
    queue_[rear++] = 0;
    in_queue_flag[0]=1;
    while(front < rear){
        int u = queue_[front++];
        if(front >= MAXN*2) front -= MAXN*2;
        in_queue_flag[u]=0;
        Edge* e = adj[u];
        while(e){
            int v = e->to;
            long long new_dist = dist_val[u] + e->weight;
            if(new_dist < dist_val[v]){
                dist_val[v] = new_dist;
                if(!in_queue_flag[v]){
                    queue_[rear++] = v;
                    if(rear >= MAXN*2) rear -= MAXN*2;
                    in_queue_flag[v]=1;
                    if(++counts[v] > n){
                        printf("No\n");
                        return 0;
                    }
                }
            }
            e = e->next;
        }
    }
    printf("Yes\n");
    return 0;
}