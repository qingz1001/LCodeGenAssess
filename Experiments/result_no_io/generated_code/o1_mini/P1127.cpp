#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_WORD_LEN 21

char words[MAX_N][MAX_WORD_LEN];
int n;
int start_chars[MAX_N], end_chars[MAX_N];
int adj[26][MAX_N];
int adj_size[26];
int route[MAX_N];
int route_size = 0;

int cmp(const void *a, const void *b){
    return strcmp((char*)a, (char*)b);
}

void dfs(int u){
    while(adj_size[u] > 0){
        adj_size[u]--;
        int word_idx = adj[u][adj_size[u]];
        dfs(end_chars[word_idx]);
        route[route_size++] = word_idx;
    }
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%s", words[i]);
    qsort(words, n, sizeof(words[0]), cmp);
    for(int i=0;i<n;i++){
        start_chars[i] = words[i][0] - 'a';
        int len = strlen(words[i]);
        end_chars[i] = words[i][len-1] - 'a';
    }
    // Build adjacency lists
    for(int i=0;i<n;i++) {
        adj[start_chars[i]][adj_size[start_chars[i]]++] = i;
    }
    // Calculate in-degree and out-degree
    int in_degree[26] = {0}, out_degree[26] = {0};
    for(int i=0;i<n;i++){
        out_degree[start_chars[i]]++;
        in_degree[end_chars[i]]++;
    }
    // Check Eulerian trail conditions
    int start_vertex = -1, end_vertex = -1;
    int cnt1 = 0, cnt2 = 0;
    for(int i=0;i<26;i++){
        if(out_degree[i] - in_degree[i] == 1){
            cnt1++;
            start_vertex = i;
        }
        if(in_degree[i] - out_degree[i] == 1){
            cnt2++;
            end_vertex = i;
        }
        if(out_degree[i] - in_degree[i] >1 || in_degree[i] - out_degree[i] >1){
            printf("***\n");
            return 0;
        }
    }
    if(!((cnt1 ==1 && cnt2 ==1) || (cnt1 ==0 && cnt2 ==0))){
        printf("***\n");
        return 0;
    }
    if(start_vertex == -1){
        for(int i=0;i<26;i++) if(out_degree[i] >0){ start_vertex = i; break;}
    }
    dfs(start_vertex);
    if(route_size != n){
        printf("***\n");
        return 0;
    }
    // Reverse the route
    for(int i=0;i < route_size /2;i++){
        int temp = route[i];
        route[i] = route[route_size -1 -i];
        route[route_size -1 -i] = temp;
    }
    // Build the output
    for(int i=0;i<route_size;i++){
        printf("%s", words[route[i]]);
        if(i != route_size -1) printf(".");
    }
    printf("\n");
    return 0;
}