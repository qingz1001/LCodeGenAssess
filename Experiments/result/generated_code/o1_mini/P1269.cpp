#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20001
#define MAX_EDGES 40002

typedef struct {
    int to;
    int atten;
} edge_t;

edge_t edges[MAX_EDGES];
int head_node[MAX_N];
int next_edge[MAX_EDGES];
int edge_count = 0;

typedef struct {
    int node;
    int parent;
    int signal;
} stack_element_t;

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 0;
    }
    // Initialize head_node
    for(int i=1;i<=n;i++) head_node[i]=-1;
    // Read adjacency list
    for(int i=1;i<=n;i++){
        int k;
        if(scanf("%d", &k)!=1){
            return 0;
        }
        for(int j=0;j<k;j++){
            int neighbor, atten;
            if(scanf("%d %d", &neighbor, &atten)!=2){
                return 0;
            }
            edges[edge_count].to = neighbor;
            edges[edge_count].atten = atten;
            next_edge[edge_count] = head_node[i];
            head_node[i] = edge_count++;
        }
    }
    int A;
    if(scanf("%d", &A)!=1){
        return 0;
    }
    // Initialize stack
    stack_element_t *stack = (stack_element_t*)malloc(sizeof(stack_element_t)*n);
    int top = 0;
    stack[top].node = 1;
    stack[top].parent = 0;
    stack[top].signal = A;
    top++;
    int count = 0;
    int impossible = 0;
    while(top >0 && !impossible){
        top--;
        stack_element_t current = stack[top];
        int node = current.node;
        int parent = current.parent;
        int signal = current.signal;
        // First pass: check if any child requires amplifier
        int need_install = 0;
        int temp_attens[MAX_N];
        int child_nodes[MAX_N];
        int child_num =0;
        int e = head_node[node];
        while(e != -1){
            int child = edges[e].to;
            int atten = edges[e].atten;
            if(child != parent){
                if(atten > A){
                    impossible =1;
                    break;
                }
                if(signal - atten <=0){
                    need_install =1;
                }
                child_nodes[child_num] = child;
                temp_attens[child_num] = atten;
                child_num++;
            }
            e = next_edge[e];
        }
        if(impossible) break;
        if(need_install){
            count++;
            for(int i=0;i<child_num;i++){
                int child = child_nodes[i];
                int atten = temp_attens[i];
                int residual = A - atten;
                if(residual <=0){
                    impossible =1;
                    break;
                }
                stack[top].node = child;
                stack[top].parent = node;
                stack[top].signal = residual;
                top++;
            }
        }
        else{
            for(int i=0;i<child_num;i++){
                int child = child_nodes[i];
                int atten = temp_attens[i];
                int residual = signal - atten;
                stack[top].node = child;
                stack[top].parent = node;
                stack[top].signal = residual;
                top++;
            }
        }
    }
    free(stack);
    if(impossible){
        printf("No solution.\n");
    }
    else{
        printf("%d\n", count);
    }
    return 0;
}