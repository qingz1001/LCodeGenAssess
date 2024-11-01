#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 20
#define ALPHABET 26

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int end;
} Edge;

typedef struct {
    Edge edges[MAX_WORDS];
    int count;
} Node;

Node graph[ALPHABET];
int in_degree[ALPHABET] = {0};
int out_degree[ALPHABET] = {0};

int cmp_edges(const void *a, const void *b) {
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    return strcmp(ea->word, eb->word);
}

int main(){
    int n;
    scanf("%d", &n);
    char word[MAX_WORD_LEN + 1];
    for(int i=0;i<n;i++){
        scanf("%s", word);
        int start = word[0] - 'a';
        int end = word[strlen(word)-1] - 'a';
        strcpy(graph[start].edges[graph[start].count].word, word);
        graph[start].edges[graph[start].count].end = end;
        graph[start].count++;
        out_degree[start]++;
        in_degree[end]++;
    }
    for(int i=0;i<ALPHABET;i++) {
        if(graph[i].count > 1){
            qsort(graph[i].edges, graph[i].count, sizeof(Edge), cmp_edges);
        }
    }
    int start_node = 0;
    int start_nodes = 0, end_nodes = 0;
    for(int i=0;i<ALPHABET;i++) {
        if(out_degree[i] - in_degree[i] == 1){
            start_node = i;
            start_nodes++;
        }
        else if(in_degree[i] - out_degree[i] == 1){
            end_nodes++;
        }
        else if(in_degree[i] != out_degree[i]){
            start_nodes = 2;
            break;
        }
    }
    if(!((start_nodes ==0 && end_nodes ==0) || (start_nodes ==1 && end_nodes ==1))){
        printf("***");
        return 0;
    }
    // Find starting node
    if(start_nodes ==0){
        for(int i=0;i<ALPHABET;i++) {
            if(out_degree[i] >0){
                start_node = i;
                break;
            }
        }
    }
    // Hierholzer's algorithm
    int stack[10000];
    int stack_size =0;
    char *result[1000];
    int res_size =0;
    int current[ALPHABET];
    for(int i=0;i<ALPHABET;i++) current[i]=0;
    stack[stack_size++] = start_node;
    while(stack_size >0){
        int u = stack[stack_size-1];
        if(current[u] < graph[u].count){
            Edge e = graph[u].edges[current[u]++];
            stack[stack_size++] = e.end;
            result[res_size++] = e.word;
        }
        else{
            stack_size--;
        }
    }
    if(res_size != n){
        printf("***");
        return 0;
    }
    // Reverse the result
    for(int i=0;i<res_size/2;i++){
        char *temp = result[i];
        result[i] = result[res_size-1-i];
        result[res_size-1-i] = temp;
    }
    // Print the chain
    for(int i=0;i<res_size;i++){
        if(i>0) printf(".");
        printf("%s", result[i]);
    }
    return 0;
}