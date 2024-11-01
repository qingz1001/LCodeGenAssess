#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 52
#define MAX_EDGES 10000
#define INF 1000000000

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

Edge* adj[MAX_NODES];
int dist_arr[MAX_NODES];
int visited[MAX_NODES];

int char_to_index(char c){
    if('a' <= c && c <= 'z') return c - 'a';
    if('A' <= c && c <= 'Y') return 26 + (c - 'A');
    if(c == 'Z') return 51;
    return -1;
}

int main(){
    int P;
    scanf("%d", &P);
    for(int i=0;i<P;i++){
        char c1, c2;
        int cost;
        scanf(" %c %c %d", &c1, &c2, &cost);
        int u = char_to_index(c1);
        int v = char_to_index(c2);
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = v;
        e1->cost = cost;
        e1->next = adj[u];
        adj[u] = e1;
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = u;
        e2->cost = cost;
        e2->next = adj[v];
        adj[v] = e2;
    }
    for(int i=0;i<MAX_NODES;i++) dist_arr[i] = INF;
    int Z = char_to_index('Z');
    dist_arr[Z] = 0;
    for(int i=0;i<MAX_NODES;i++) visited[i] = 0;
    for(int i=0;i<MAX_NODES;i++){
        int u = -1, min = INF;
        for(int v=0;v<MAX_NODES;v++) if(!visited[v] && dist_arr[v] < min){ min = dist_arr[v]; u = v;}
        if(u == -1) break;
        visited[u] = 1;
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            if(dist_arr[u] + e->cost < dist_arr[e->to]){
                dist_arr[e->to] = dist_arr[u] + e->cost;
            }
        }
    }
    char res;
    int min_dist = INF;
    for(int i=26;i<51;i++){ // 'A' to 'Y'
        if(dist_arr[i] < min_dist){
            min_dist = dist_arr[i];
            res = (char)(i - 26 + 'A');
        }
    }
    printf("%c %d\n", res, min_dist);
    return 0;
}