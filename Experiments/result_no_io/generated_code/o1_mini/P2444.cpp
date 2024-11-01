#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXNODES 30005
#define QUEUE_SIZE 30005

typedef struct Node {
    int children[2];
    int fail;
    int terminal;
} Node;

Node nodes[MAXNODES];
int node_count = 1;

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        char s[10005];
        scanf("%s", s);
        int current = 0;
        for(int j=0; s[j]; j++){
            int c = s[j]-'0';
            if(nodes[current].children[c] == 0){
                nodes[current].children[c] = node_count;
                nodes[node_count].fail = 0;
                nodes[node_count].terminal = 0;
                nodes[node_count].children[0] = 0;
                nodes[node_count].children[1] = 0;
                node_count++;
            }
            current = nodes[current].children[c];
        }
        nodes[current].terminal = 1;
    }
    // Initialize queue for BFS
    int queue[QUEUE_SIZE];
    int front=0, rear=0;
    // Initialize root's fail
    nodes[0].fail = 0;
    // Set fail links for depth 1
    for(int c=0; c<2; c++){
        int child = nodes[0].children[c];
        if(child){
            nodes[child].fail = 0;
            queue[rear++] = child;
        }
        else{
            nodes[0].children[c] = 0;
        }
    }
    // BFS to set fail links
    while(front < rear){
        int current = queue[front++];
        for(int c=0; c<2; c++){
            int child = nodes[current].children[c];
            if(child){
                int fail = nodes[current].fail;
                while(nodes[fail].children[c] == 0 && fail != 0){
                    fail = nodes[fail].fail;
                }
                if(nodes[fail].children[c]){
                    nodes[child].fail = nodes[fail].children[c];
                }
                else{
                    nodes[child].fail = 0;
                }
                if(nodes[nodes[child].fail].terminal){
                    nodes[child].terminal = 1;
                }
                queue[rear++] = child;
            }
            else{
                nodes[current].children[c] = nodes[nodes[current].fail].children[c];
            }
        }
    }
    // DFS to detect cycle in non-terminal states
    int state = 0;
    int *visited = (int*)calloc(node_count, sizeof(int));
    int hasCycle = 0;
    // Iterative DFS with stack
    typedef struct StackNode {
        int current;
        int next_child;
    } StackNode;
    StackNode stack_nodes[MAXNODES];
    int stack_top = 0;
    stack_nodes[stack_top].current = 0;
    stack_nodes[stack_top].next_child = 0;
    stack_top++;
    while(stack_top > 0 && !hasCycle){
        stack_top--;
        int current = stack_nodes[stack_top].current;
        int child_start = stack_nodes[stack_top].next_child;
        if(child_start == 0){
            if(visited[current] == 1){
                hasCycle = 1;
                break;
            }
            if(nodes[current].terminal){
                continue;
            }
            visited[current] = 1;
        }
        while(child_start < 2){
            int c = child_start;
            child_start++;
            stack_nodes[stack_top].next_child = child_start;
            int next = nodes[current].children[c];
            if(!nodes[next].terminal){
                if(visited[next] == 1){
                    hasCycle = 1;
                    break;
                }
                if(visited[next] == 0){
                    stack_nodes[stack_top].current = next;
                    stack_nodes[stack_top].next_child = 0;
                    stack_top++;
                }
            }
        }
        if(child_start >=2 ){
            visited[current] = 2;
        }
    }
    if(hasCycle){
        printf("TAK");
    }
    else{
        printf("NIE");
    }
    free(visited);
    return 0;
}