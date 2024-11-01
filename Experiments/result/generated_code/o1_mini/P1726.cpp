#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5001
#define MAXM 100000

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int index_counter = 1;
int indices_arr[MAXN];
int lowlink_arr[MAXN];
int on_stack_arr[MAXN];
int stack_arr[MAXN];
int stack_top = -1;

typedef struct SCC {
    int size;
    int nodes[MAXN];
} SCC;

SCC sccs[MAXN];
int scc_count = 0;

void add_edge(int from, int to){
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->next = adj[from];
    adj[from] = new_edge;
}

int min(int a, int b){
    return a < b ? a : b;
}

int cmp_int(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

void strongconnect(int v){
    indices_arr[v] = index_counter;
    lowlink_arr[v] = index_counter;
    index_counter++;
    stack_arr[++stack_top] = v;
    on_stack_arr[v] = 1;

    Edge* edge = adj[v];
    while(edge){
        int w = edge->to;
        if(indices_arr[w] == 0){
            strongconnect(w);
            lowlink_arr[v] = min(lowlink_arr[v], lowlink_arr[w]);
        }
        else if(on_stack_arr[w]){
            lowlink_arr[v] = min(lowlink_arr[v], indices_arr[w]);
        }
        edge = edge->next;
    }

    if(lowlink_arr[v] == indices_arr[v]){
        SCC current_scc;
        current_scc.size = 0;
        while(1){
            int w = stack_arr[stack_top--];
            on_stack_arr[w] = 0;
            current_scc.nodes[current_scc.size++] = w;
            if(w == v) break;
        }
        // Sort the current SCC nodes
        qsort(current_scc.nodes, current_scc.size, sizeof(int), cmp_int);
        // Add to sccs
        sccs[scc_count++] = current_scc;
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=0;i<=N;i++) adj[i] = NULL;
    for(int i=0;i<M;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        if(t == 1){
            add_edge(a, b);
        }
        else{
            add_edge(a, b);
            add_edge(b, a);
        }
    }
    for(int v=1; v<=N; v++){
        if(indices_arr[v] == 0){
            strongconnect(v);
        }
    }
    // Find the largest SCC, and lex smallest if tie
    int best_size = 0;
    int best_list[MAXN];
    int best_len = 0;
    for(int i=0;i<scc_count;i++){
        if(sccs[i].size > best_size){
            best_size = sccs[i].size;
            best_len = sccs[i].size;
            for(int j=0;j<sccs[i].size;j++) best_list[j] = sccs[i].nodes[j];
        }
        else if(sccs[i].size == best_size){
            // Compare lex order
            int smaller = 0;
            for(int j=0;j<sccs[i].size;j++){
                if(j >= best_size) { smaller = 1; break; }
                if(sccs[i].nodes[j] < best_list[j]){
                    smaller = 1;
                    break;
                }
                else if(sccs[i].nodes[j] > best_list[j]){
                    break;
                }
            }
            if(smaller){
                best_len = sccs[i].size;
                for(int j=0;j<sccs[i].size;j++) best_list[j] = sccs[i].nodes[j];
            }
        }
    }
    // Print the result
    printf("%d\n", best_size);
    for(int i=0;i<best_size;i++) printf("%d%c", best_list[i], i < best_size-1 ? ' ' : '\n');
    // Free memory
    for(int i=1;i<=N;i++){
        Edge* edge = adj[i];
        while(edge){
            Edge* tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }
    return 0;
}