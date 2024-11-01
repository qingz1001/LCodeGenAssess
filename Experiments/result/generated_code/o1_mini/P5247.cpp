#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5001
#define MAXQ 500000
#define MAXNEIGH 5000

typedef struct {
    int neighbors[MAXNEIGH];
    int count;
} Node;

Node graph[MAXN];
int visited[MAXN];
int visit_token = 1;
int queue_buffer[MAXN];

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2){
        return 0;
    }
    int last = 0;
    for(int i=0; i<m; i++){
        int op, x, y;
        if(scanf("%d %d %d", &op, &x, &y)!=3){
            break;
        }
        int u = x ^ last;
        int v = y ^ last;
        if(u > v){
            int temp = u;
            u = v;
            v = temp;
        }
        if(op == 0){
            // Add edge u-v
            graph[u].neighbors[graph[u].count++] = v;
            graph[v].neighbors[graph[v].count++] = u;
        }
        else if(op ==1){
            // Remove edge u-v
            // Remove v from u's list
            int found = 0;
            for(int j=0; j<graph[u].count; j++){
                if(graph[u].neighbors[j] == v){
                    graph[u].neighbors[j] = graph[u].neighbors[graph[u].count -1];
                    graph[u].count--;
                    break;
                }
            }
            // Remove u from v's list
            for(int j=0; j<graph[v].count; j++){
                if(graph[v].neighbors[j] == u){
                    graph[v].neighbors[j] = graph[v].neighbors[graph[v].count -1];
                    graph[v].count--;
                    break;
                }
            }
        }
        else if(op ==2){
            // Query connectivity between u and v
            if(u == v){
                printf("Y\n");
                last = u;
                continue;
            }
            int front =0, back =0;
            queue_buffer[back++] = u;
            visited[u] = visit_token;
            int found = 0;
            while(front < back){
                int current = queue_buffer[front++];
                for(int j=0; j<graph[current].count; j++){
                    int nei = graph[current].neighbors[j];
                    if(visited[nei] != visit_token){
                        visited[nei] = visit_token;
                        if(nei == v){
                            found =1;
                            break;
                        }
                        queue_buffer[back++] = nei;
                    }
                }
                if(found){
                    break;
                }
            }
            if(found){
                printf("Y\n");
                last = u;
            }
            else{
                printf("N\n");
                last = v;
            }
            visit_token++;
        }
    }
    return 0;
}