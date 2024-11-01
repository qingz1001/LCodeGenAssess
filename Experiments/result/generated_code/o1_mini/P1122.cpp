#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 16000
#define MAXE (2 * (MAXN))

typedef struct {
    int node;
    int parent;
    int processed;
} StackNode;

int main(){
    int n;
    scanf("%d", &n);
    int *beauty = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &beauty[i]);
    
    int *head = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) head[i]=-1;
    
    int *to = (int*)malloc(MAXE * sizeof(int));
    int *next_edge = (int*)malloc(MAXE * sizeof(int));
    int edge_cnt = 0;
    
    for(int i=0;i<n-1;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        to[edge_cnt] = b;
        next_edge[edge_cnt] = head[a];
        head[a] = edge_cnt++;
        
        to[edge_cnt] = a;
        next_edge[edge_cnt] = head[b];
        head[b] = edge_cnt++;
    }
    
    StackNode *stack = (StackNode*)malloc((n * 2) * sizeof(StackNode));
    int top = 0;
    stack[top].node = 0;
    stack[top].parent = -1;
    stack[top].processed = 0;
    top++;
    
    int *maxSum = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) maxSum[i] = 0;
    
    int global_max = INT_MIN;
    
    while(top > 0){
        StackNode current = stack[--top];
        if(!current.processed){
            stack[top].node = current.node;
            stack[top].parent = current.parent;
            stack[top].processed = 1;
            top++;
            int e = head[current.node];
            while(e != -1){
                int neighbor = to[e];
                if(neighbor != current.parent){
                    stack[top].node = neighbor;
                    stack[top].parent = current.node;
                    stack[top].processed = 0;
                    top++;
                }
                e = next_edge[e];
            }
        }
        else{
            int sum = beauty[current.node];
            int e = head[current.node];
            while(e != -1){
                int neighbor = to[e];
                if(neighbor != current.parent){
                    if(maxSum[neighbor] > 0){
                        sum += maxSum[neighbor];
                    }
                }
                e = next_edge[e];
            }
            maxSum[current.node] = sum;
            if(sum > global_max){
                global_max = sum;
            }
        }
    }
    
    printf("%d\n", global_max);
    
    free(beauty);
    free(head);
    free(to);
    free(next_edge);
    free(stack);
    free(maxSum);
    
    return 0;
}