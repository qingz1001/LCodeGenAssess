#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

#define MAX 100005

Edge* adj[MAX];
double f_ans[MAX];
double E_ans[MAX];
int n, m;

// Stack for iterative DFS
typedef struct StackNode {
    int u;
    int parent;
    int state;
} StackNode;

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = y;
        e1->weight = w;
        e1->next = adj[x];
        adj[x] = e1;
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = x;
        e2->weight = w;
        e2->next = adj[y];
        adj[y] = e2;
    }

    // Choose root as 1
    // First DFS to compute f[u] when parent is p
    double f_subtree[MAX];
    int parent[MAX];
    memset(parent, -1, sizeof(parent));
    // Initialize f_subtree
    for(int i=1;i<=n;i++) f_subtree[i] = 0.0;

    // Iterative DFS
    StackNode stack[2*MAX];
    int top = 0;
    stack[top].u = 1;
    stack[top].parent = -1;
    stack[top].state = 0;
    top++;
    while(top > 0){
        top--;
        StackNode current = stack[top];
        int u = current.u;
        int p = current.parent;
        if(current.state == 0){
            // Push back with state=1
            stack[top].u = u;
            stack[top].parent = p;
            stack[top].state = 1;
            top++;
            // Push children
            for(Edge* e = adj[u]; e != NULL; e = e->next){
                if(e->to != p){
                    stack[top].u = e->to;
                    stack[top].parent = u;
                    stack[top].state = 0;
                    top++;
                }
            }
        }
        else{
            // Compute f_subtree[u]
            int degree = 0;
            for(Edge* e = adj[u]; e != NULL; e = e->next){
                if(e->to != p) degree++;
            }
            if(degree == 0){
                f_subtree[u] = 0.0;
            }
            else{
                double sum = 0.0;
                for(Edge* e = adj[u]; e != NULL; e = e->next){
                    if(e->to != p){
                        sum += (1.0 / degree) * ( (double)e->weight + f_subtree[e->to]);
                    }
                }
                f_subtree[u] = sum;
            }
        }
    }

    // Now rerooting to compute E_ans for all nodes
    // Initialize E_ans[1] = f_subtree[1]
    // Then perform another DFS to propagate
    for(int i=1;i<=n;i++) E_ans[i] = 0.0;
    E_ans[1] = f_subtree[1];

    // Another iterative DFS for rerooting
    top = 0;
    stack[top].u = 1;
    stack[top].parent = -1;
    stack[top].state = 0;
    top++;
    while(top > 0){
        top--;
        StackNode current = stack[top];
        int u = current.u;
        int p = current.parent;
        if(current.state == 0){
            // Push back with state=1
            stack[top].u = u;
            stack[top].parent = p;
            stack[top].state = 1;
            top++;
            // Push children
            for(Edge* e = adj[u]; e != NULL; e = e->next){
                if(e->to != p){
                    stack[top].u = e->to;
                    stack[top].parent = u;
                    stack[top].state = 0;
                    top++;
                }
            }
        }
        else{
            // After children
            for(Edge* e = adj[u]; e != NULL; e = e->next){
                int c = e->to;
                if(c != p){
                    // Compute E_ans[c]
                    int deg_u = 0;
                    for(Edge* ex = adj[u]; ex != NULL; ex = ex->next){
                        if(ex->to != p) deg_u++;
                    }
                    double prob = 1.0 / deg_u;
                    E_ans[c] = E_ans[u] + ( (double)e->weight ) - ( prob * ((double)e->weight + f_subtree[c]) );
                }
            }
        }
    }

    // To handle E_ans correctly, perform a proper rerooting
    // Reset E_ans and perform proper rerooting
    for(int i=1;i<=n;i++) E_ans[i] = 0.0;
    // Second pass to compute E_ans properly
    // Implemented as recursive rerooting, but using iterative approach
    // Recompute f_subtree
    memset(parent, -1, sizeof(parent));
    top = 0;
    stack[top].u = 1;
    stack[top].parent = -1;
    stack[top].state = 0;
    top++;
    while(top > 0){
        StackNode current = stack[top-1];
        if(current.state == 0){
            stack[top-1].state = 1;
            for(Edge* e = adj[current.u]; e != NULL; e = e->next){
                if(e->to != current.parent){
                    stack[top].u = e->to;
                    stack[top].parent = current.u;
                    stack[top].state = 0;
                    top++;
                }
            }
        }
        else{
            top--;
            int u = current.u;
            int p = current.parent;
            if(u == 1){
                E_ans[u] = f_subtree[u];
            }
            else{
                // Find the edge weight between p and u
                int w = 0;
                for(Edge* e = adj[p]; e != NULL; e = e->next){
                    if(e->to == u){
                        w = e->weight;
                        break;
                    }
                }
                // E_ans[u] = E_ans[p] + w - ( (1.0 / (deg_p)) * (w + f_subtree[u]) )
                int deg_p = 0;
                for(Edge* e = adj[p]; e != NULL; e = e->next){
                    if(e->to != parent[p]) deg_p++;
                }
                E_ans[u] = E_ans[p] + (double)w - ( (1.0 / (double)deg_p ) * ( (double)w + f_subtree[u] ));
            }
            // Update f_subtree if needed
        }
    }

    // Finally, compute the sum of E_ans
    double total = 0.0;
    for(int i=1;i<=n;i++) total += E_ans[i];
    // Compute average
    double average = total / (double)n;
    // Print with five decimal places
    printf("%.5lf\n", average);
    return 0;
}