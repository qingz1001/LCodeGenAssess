#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 366666
#define LOG 20

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

Edge* adjT[MAXN + 1];
Edge* adjTprime[MAXN + 1];
long long depthT[MAXN + 1];
long long depthTprime[MAXN + 1];
int parentT[LOG][MAXN + 1];
int depth_levelT[MAXN + 1];
int parentTprime[LOG][MAXN + 1];
int depth_levelTprime_arr[MAXN + 1];

long long max_result = LLONG_MIN;

void addEdge(Edge* adj[], int from, int to, int weight){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->weight = weight;
    edge->next = adj[from];
    adj[from] = edge;
}

void dfsT(int u, int p){
    parentT[0][u] = p;
    for(int i=1;i<LOG;i++){
        parentT[i][u] = parentT[i-1][parentT[i-1][u]];
    }
    Edge* e = adjT[u];
    while(e){
        int v = e->to;
        if(v != p){
            depthT[v] = depthT[u] + e->weight;
            depth_levelT[v] = depth_levelT[u] + 1;
            dfsT(v, u);
        }
        e = e->next;
    }
}

int lcaT(int u, int v){
    if(depth_levelT[u] < depth_levelT[v]){
        int temp = u;
        u = v;
        v = temp;
    }
    for(int k=LOG-1; k>=0; k--){
        if(depth_levelT[u] - (1<<k) >= depth_levelT[v]){
            u = parentT[k][u];
        }
    }
    if(u == v) return u;
    for(int k=LOG-1; k>=0; k--){
        if(parentT[k][u] != parentT[k][v]){
            u = parentT[k][u];
            v = parentT[k][v];
        }
    }
    return parentT[0][u];
}

void dfsTprime(int u, int p){
    parentTprime[0][u] = p;
    for(int i=1;i<LOG;i++){
        parentTprime[i][u] = parentTprime[i-1][parentTprime[i-1][u]];
    }
    Edge* e = adjTprime[u];
    while(e){
        int v = e->to;
        if(v != p){
            depthTprime[v] = depthTprime[u] + e->weight;
            depth_levelTprime_arr[v] = depth_levelTprime_arr[u] + 1;
            dfsTprime(v, u);
        }
        e = e->next;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<2*n-2;i++){
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        if(i < n-1){
            addEdge(adjT, x, y, v);
            addEdge(adjT, y, x, v);
        }
        else{
            addEdge(adjTprime, x, y, v);
            addEdge(adjTprime, y, x, v);
        }
    }
    // Initialize depth
    depthT[1] = 0;
    depth_levelT[1] = 0;
    dfsT(1,1);
    depthTprime[1] = 0;
    depth_levelTprime_arr[1] = 0;
    dfsTprime(1,1);
    
    // Now process T' to find maximum
    // We need to traverse T' and for each node, keep top two depthT
    // Implemented via DFS
    typedef struct Pair {
        long long val;
        int node;
    } Pair;
    
    Pair best1[MAXN +1];
    Pair best2[MAXN +1];
    
    // Initialize
    for(int i=1;i<=n;i++){
        best1[i].val = depthT[i];
        best1[i].node = i;
        best2[i].val = LLONG_MIN;
        best2[i].node = -1;
    }
    
    // Post-order traversal
    // Implemented iteratively to avoid stack overflow
    typedef struct StackNode {
        int u;
        int p;
        int state;
    } StackNode;
    
    StackNode stack_stack[MAXN * 2];
    int stack_ptr = 0;
    stack_stack[stack_ptr++] = (StackNode){1, -1, 0};
    
    while(stack_ptr > 0){
        StackNode current = stack_stack[--stack_ptr];
        int u = current.u;
        int p = current.p;
        if(current.state == 0){
            // Push back with state=1
            stack_stack[stack_ptr++] = (StackNode){u, p, 1};
            // Push children
            Edge* e = adjTprime[u];
            while(e){
                int v = e->to;
                if(v != p){
                    stack_stack[stack_ptr++] = (StackNode){v, u, 0};
                }
                e = e->next;
            }
        }
        else{
            // Combine children's best1 and best2
            Edge* e = adjTprime[u];
            while(e){
                int v = e->to;
                if(v != p){
                    if(best1[v].val > best1[u].val){
                        best2[u] = best1[u];
                        best1[u] = best1[v];
                    }
                    else if(best1[v].val > best2[u].val){
                        best2[u] = best1[v];
                    }
                }
                e = e->next;
            }
            // Now, for node u, check if it has at least two best
            if(best2[u].val != LLONG_MIN){
                // Compute LCA in T
                int lca = lcaT(best1[u].node, best2[u].node);
                long long expr = depthT[best1[u].node] + depthT[best2[u].node] - depthT[lca] - depthTprime[u];
                if(expr > max_result){
                    max_result = expr;
                }
            }
        }
    }
    
    printf("%lld\n", max_result);
    
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = adjT[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
        e = adjTprime[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return 0;
}