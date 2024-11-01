#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 52
#define INF INT_MAX

int graph[MAX_NODES][MAX_NODES];
int dist[MAX_NODES];
int visited[MAX_NODES];

int char_to_index(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    return -1;
}

char index_to_char(int i) {
    if (i < 26) return 'a' + i;
    return 'A' + (i - 26);
}

void dijkstra(int start) {
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    
    dist[start] = 0;
    
    for (int count = 0; count < MAX_NODES - 1; count++) {
        int min_dist = INF, min_index = -1;
        
        for (int v = 0; v < MAX_NODES; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                min_index = v;
            }
        }
        
        if (min_index == -1) break;
        
        visited[min_index] = 1;
        
        for (int v = 0; v < MAX_NODES; v++) {
            if (!visited[v] && graph[min_index][v] && dist[min_index] != INF
                && dist[min_index] + graph[min_index][v] < dist[v]) {
                dist[v] = dist[min_index] + graph[min_index][v];
            }
        }
    }
}

int main() {
    int P;
    scanf("%d", &P);
    
    memset(graph, 0, sizeof(graph));
    
    for (int i = 0; i < P; i++) {
        char a, b;
        int len;
        scanf(" %c %c %d", &a, &b, &len);
        int ia = char_to_index(a);
        int ib = char_to_index(b);
        if (graph[ia][ib] == 0 || len < graph[ia][ib]) {
            graph[ia][ib] = graph[ib][ia] = len;
        }
    }
    
    int barn = char_to_index('Z');
    dijkstra(barn);
    
    int min_dist = INF;
    char fastest_cow = 0;
    
    for (int i = 26; i < 51; i++) {
        if (dist[i] < min_dist) {
            min_dist = dist[i];
            fastest_cow = index_to_char(i);
        }
    }
    
    printf("%c %d\n", fastest_cow, min_dist);
    
    return 0;
}