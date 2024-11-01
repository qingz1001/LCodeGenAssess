#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    int attenuation;
    struct Edge* next;
} Edge;

#define MAXN 20001

Edge* adj[MAXN];
int S;
int count_amp = 0;
int impossible_flag = 0;

void add_edge(int from, int to, int atten){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->attenuation = atten;
    e->next = adj[from];
    adj[from] = e;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        int k;
        scanf("%d", &k);
        for(int j=0;j<k;j++){
            int neighbor, atten;
            scanf("%d %d", &neighbor, &atten);
            add_edge(i, neighbor, atten);
        }
    }
    scanf("%d", &S);
    // Iterative DFS
    typedef struct {
        int node;
        int signal;
        int parent;
        Edge* edge;
    } Frame;
    Frame* stack = (Frame*)malloc(sizeof(Frame) * (n+1));
    int top = 0;
    stack[top].node = 1;
    stack[top].signal = S;
    stack[top].parent = -1;
    stack[top].edge = adj[1];
    top++;
    while(top >0 && !impossible_flag){
        top--;
        Frame current = stack[top];
        int node = current.node;
        int signal = current.signal;
        Edge* e = current.edge;
        while(e){
            int child = e->to;
            if(child != current.parent){
                int residual = signal - e->attenuation;
                if(residual > 0){
                    // Push child to stack with residual
                    stack[top].node = child;
                    stack[top].signal = residual;
                    stack[top].parent = node;
                    stack[top].edge = adj[child];
                    top++;
                }
                else{
                    // Need to install amplifier at current node
                    count_amp++;
                    if(S - e->attenuation <=0){
                        impossible_flag = 1;
                        break;
                    }
                    else{
                        // Push child with S - attenuation
                        stack[top].node = child;
                        stack[top].signal = S - e->attenuation;
                        stack[top].parent = node;
                        stack[top].edge = adj[child];
                        top++;
                    }
                }
            }
            e = e->next;
        }
    }
    if(impossible_flag){
        printf("No solution.\n");
    }
    else{
        printf("%d\n", count_amp);
    }
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(stack);
    return 0;
}